#include "datasql.h"

DataSql::DataSql(const DataSql& data): InterfaceSaver(data)
{}

DataSql::~DataSql()
{
    if(m_db.isOpen()) {
        m_db.close();
    }
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
}

void DataSql::initMetadataRequest()
{
//    m_createMetadataRequest = QSharedPointer<QSqlQuery>::create("", m_db);
//    m_selectMetadataRequest = QSharedPointer<QSqlQuery>::create("", m_db);
//    m_removeMetadataRequest = QSharedPointer<QSqlQuery>::create("", m_db);
    m_updateMetadataRequest = QSharedPointer<QSqlQuery>::create("", m_db);

//    qDebug()<<"Create Metadata request"<<m_createMetadataRequest->prepare("INSERT INTO metadata (id, name, value, pid) VALUES (:id, :name, :value, :pid)")<<m_createMetadataRequest->lastError();
//    qDebug()<<"Select Metadata request"<<m_selectMetadataRequest->prepare("SELECT * FROM metadata WHERE id = :id")<<m_selectMetadataRequest->lastError();
//    qDebug()<<"Remove Metadata request"<<m_removeMetadataRequest->prepare("DELETE FROM metadata WHERE id = :id")<<m_removeMetadataRequest->lastError();
    qDebug()<<"Updata Metadata request"<<m_updateMetadataRequest->prepare("UPDATE metadata SET value=:value WHERE id = :id AND name=:name")<<m_updateMetadataRequest->lastError();
}

void DataSql::initProbeRequest() {}
void DataSql::initSourceDirRequest() {}

QMap<QUuid, LibraryPointer> DataSql::selectLibrary() const
{
    return m_libraries;
}

bool DataSql::updateMetadata(QUuid id, QString name, QVariant value)
{
    m_updateMetadataRequest->bindValue(":id", id.toString());
    m_updateMetadataRequest->bindValue(":name", name);
    m_updateMetadataRequest->bindValue(":value", value);
    return m_updateMetadataRequest->exec();
}

bool DataSql::createLibrary(QString name, MediaPlayerGlobal::MediaRole role)
{
    auto lib = factory<Library>();
    lib->setId(QUuid::createUuid());
    m_libraries[lib->id()] = lib;

    lib->setName(name);
    lib->setRole(role);
    auto all = factory<SmartPlaylist>();

    lib->addSmartPlaylist(all);
    all->setName("All");

    m_createLibraryRequest->bindValue(":id", lib->id().toString());
    auto res = m_createLibraryRequest->exec();

    res &= updateMetadata(lib->id(), "name", name);
    res &= updateMetadata(lib->id(), "role", int(role));


    if(res) {
         emit librariesChanged();
    }
    else {
        m_removeLibraryRequest->bindValue(":id", lib->id().toString());
        m_removeLibraryRequest->exec();
    }

    return res;
}

bool DataSql::removeLibrary(QString id)
{
    m_removeLibraryRequest->bindValue(":id", id);
    auto res = m_removeLibraryRequest->exec();

    if(res) {
        m_libraries.remove(QUuid::fromString(id));
        emit librariesChanged();
    }
    return false;
}

bool DataSql::updateLibrary(LibraryPointer)
{
    //DO NOTHING
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
