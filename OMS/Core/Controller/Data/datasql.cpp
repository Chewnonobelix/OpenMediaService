#include "datasql.h"

DataSql::DataSql(const DataSql& data): InterfaceSaver(data)
{}

DataSql::~DataSql()
{
    if(m_db.isOpen()) {
        m_db.close();
    }
}

void DataSql::connectLibrary(LibraryPointer l)
{
    connect(l.data(), &Library::libraryChanged, [l, this]() {
        updateLibrary(l);
    });
}

void DataSql::initLibRequest()
{
    m_createLibraryRequest = QSharedPointer<QSqlQuery>::create("", m_db);
    m_selectLibraryRequest = QSharedPointer<QSqlQuery>::create("", m_db);
    m_removeLibraryRequest = QSharedPointer<QSqlQuery>::create("", m_db);

    qDebug()<<"Create Library request"<<m_createLibraryRequest->prepare("INSERT INTO library (id) VALUES (:id)")<<m_createLibraryRequest->lastError();
    qDebug()<<"Select Library request"<<m_selectLibraryRequest->prepare("SELECT * FROM library")<<m_selectLibraryRequest->lastError();
    qDebug()<<"Remove Library request"<<m_removeLibraryRequest->prepare("DELETE FROM library WHERE id = :id")<<m_removeLibraryRequest->lastError();
}

void DataSql::initMediaRequest()
{}
void DataSql::initPlaylistRequest()
{
    m_createPlaylistRequest = QSharedPointer<QSqlQuery>::create("", m_db);
    m_selectPlaylistRequest = QSharedPointer<QSqlQuery>::create("", m_db);
    m_removePlaylistRequest = QSharedPointer<QSqlQuery>::create("", m_db);

    qDebug()<<"Create Playlist request"<<m_createPlaylistRequest->prepare("INSERT INTO playlist (id, lib, smart) VALUES (:id, :lib, :smart)")<<m_createPlaylistRequest->lastError();
    qDebug()<<"Select Playlist request"<<m_selectPlaylistRequest->prepare("SELECT * FROM playlist WHERE lib=:lib")<<m_selectPlaylistRequest->lastError();
    qDebug()<<"Remove Playlist request"<<m_removePlaylistRequest->prepare("DELETE FROM playlist WHERE id = :id")<<m_removePlaylistRequest->lastError();
}

void DataSql::initMetadataRequest()
{
    m_createMetadataRequest = QSharedPointer<QSqlQuery>::create("", m_db);
    m_selectMetadataRequest = QSharedPointer<QSqlQuery>::create("", m_db);
    m_removeMetadataRequest = QSharedPointer<QSqlQuery>::create("", m_db);
    m_updateMetadataRequest = QSharedPointer<QSqlQuery>::create("", m_db);

    qDebug()<<"Create Metadata request"<<m_createMetadataRequest->prepare("INSERT INTO metadata (id, name, value, pid) VALUES (:id, :name, :value, :pid)")<<m_createMetadataRequest->lastError();
    qDebug()<<"Select Metadata request"<<m_selectMetadataRequest->prepare("SELECT * FROM metadata WHERE id = :id")<<m_selectMetadataRequest->lastError();
    qDebug()<<"Remove Metadata request"<<m_removeMetadataRequest->prepare("DELETE FROM metadata WHERE id = :id")<<m_removeMetadataRequest->lastError();
    qDebug()<<"Updata Metadata request"<<m_updateMetadataRequest->prepare("UPDATE metadata SET name=:name, value=:value WHERE id = :id")<<m_updateMetadataRequest->lastError();
}

void DataSql::initProbeRequest() {}
void DataSql::initSourceDirRequest() {}

QMap<QUuid, LibraryPointer> DataSql::selectLibrary()
{
    auto ret = QMap<QUuid, LibraryPointer>();
    if(m_db.isOpen()) {
        auto res = m_selectLibraryRequest->exec();
        qDebug()<<m_selectLibraryRequest->lastError();

        while(m_selectLibraryRequest->next()) {
            auto l = factory<Library>();
            auto id = m_selectLibraryRequest->value("id");
            l->setId(id.toUuid());

            m_selectMetadataRequest->bindValue(":id", id);
            m_selectMetadataRequest->exec();

            qDebug()<<"Select library"<<l->id()<<m_selectMetadataRequest->lastError();

            while(m_selectMetadataRequest->next()) {
                l->setMetadata(m_selectMetadataRequest->value("name").toString(), m_selectMetadataRequest->value("value"));
            }

            selectMedia(l);
            selectPlaylist(l);

            m_libraries[l->id()] = l;
            connectLibrary(l);
        }
    }
    return m_libraries;
}

bool DataSql::createLibrary(QString name, MediaPlayerGlobal::MediaRole role)
{
    auto l = factory<Library>();
    l->setId(QUuid::createUuid());
    l->setRole(role);
    l->setName(name);
    m_libraries[l->id()] = l;
    connectLibrary(l);

    SmartPlaylistPointer all = factory<SmartPlaylist>();
    all->setName("All");
    l->addSmartPlaylist(all);

    if(m_db.isOpen()) {
        m_createLibraryRequest->bindValue(":id", l->id().toString(QUuid::StringFormat::WithoutBraces));

        auto res = m_createLibraryRequest->exec();

        qDebug()<<res<<m_createLibraryRequest->lastError()<<m_createLibraryRequest->lastQuery()<<m_createLibraryRequest->executedQuery();


        createMeta(l->id(), {"name", "role", "isShared"}, {l->name(), QString::number(int(l->role())), QString::number(false)});

        addPlaylist(l);
        if(res)
            emit librariesChanged();

        return res;
    }
    return false;
}

bool DataSql::removeLibrary(QString id)
{
    auto uid = QUuid::fromString(id);
    auto ret = m_libraries.remove(uid) > 0;
    m_removeLibraryRequest->bindValue(":id", uid.toString(QUuid::StringFormat::WithoutBraces));
    ret &= m_removeLibraryRequest->exec();

    qDebug()<<"Remove lib"<<id<<ret<<m_removeLibraryRequest->lastError();

    return ret;
}

bool DataSql::updateLibrary(LibraryPointer)
{
    return true;
}

void DataSql::init()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", "default");
    m_db.setDatabaseName("oms");
    m_db.open();
    qDebug()<<"SQL Database"<<m_db.connectionName()<<m_db.isOpen();

    if(m_db.isOpen()) {
        initLibRequest();
        initMediaRequest();
        initPlaylistRequest();
        initMetadataRequest();
        initProbeRequest();
        initSourceDirRequest();
    }
}

void DataSql::addPlaylist(LibraryPointer l)
{
    for(auto it: l->smartPlaylist()) {
        m_createPlaylistRequest->bindValue(":id", it->id().toString(QUuid::StringFormat::WithoutBraces));
        m_createPlaylistRequest->bindValue(":lib", l->id().toString(QUuid::StringFormat::WithoutBraces));
        m_createPlaylistRequest->bindValue(":smart", it->rules()->id().toString(QUuid::StringFormat::WithoutBraces));

        m_createPlaylistRequest->exec();
        qDebug()<<m_createPlaylistRequest->lastError();


//        createMeta(it->id(), "name", it->name());
    }
    for(auto it: l->playlist()) {
        m_createPlaylistRequest->bindValue(":id", it->id().toString(QUuid::StringFormat::WithoutBraces));
        m_createPlaylistRequest->bindValue(":lib", l->id().toString(QUuid::StringFormat::WithoutBraces));
        m_createPlaylistRequest->bindValue(":smart", QUuid().toString(QUuid::StringFormat::WithoutBraces));

        m_createPlaylistRequest->exec();
        qDebug()<<m_createPlaylistRequest->lastError();


//        createMeta(it->id(), "name", it->name());
    }
}

void DataSql::addMedia(LibraryPointer) {}

void DataSql::removePlaylist(LibraryPointer) {}
void DataSql::removeMedia(LibraryPointer) {}

void DataSql::updatePlaylist(LibraryPointer) {}
void DataSql::updateMedia(LibraryPointer) {}

void DataSql::selectPlaylist(LibraryPointer) const {}
void DataSql::selectMedia(LibraryPointer) const {}

void DataSql::createMeta (QUuid id, QStringList name, auto value)
{
    m_createMetadataRequest->bindValue(":id", id.toString(QUuid::StringFormat::WithoutBraces));
    m_createMetadataRequest->bindValue(":pid", QUuid::createUuid().toString(QUuid::StringFormat::WithoutBraces));
    m_createMetadataRequest->bindValue(":name", name);
    m_createMetadataRequest->bindValue(":value", value);

    m_createMetadataRequest->execBatch();

    qDebug()<<m_createMetadataRequest->lastError();
};
