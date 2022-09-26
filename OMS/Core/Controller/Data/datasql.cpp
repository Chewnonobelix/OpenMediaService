#include "datasql.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQueryModel>
#include <QSqlTableModel>

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
    m_createLibraryRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_selectLibraryRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_removeLibraryRequest = QSharedPointer<QSqlQuery>::create(m_db);

    qDebug()<<"Create Library request"<<m_createLibraryRequest->prepare("INSERT INTO library (id) VALUES (:id)")<<m_createLibraryRequest->lastError();
    qDebug()<<"Select Library request"<<m_selectLibraryRequest->prepare("SELECT * FROM library")<<m_selectLibraryRequest->lastError();
    qDebug()<<"Remove Library request"<<m_removeLibraryRequest->prepare("DELETE FROM library WHERE id = :id")<<m_removeLibraryRequest->lastError();
}

void DataSql::initMediaRequest()
{
    m_createMediaRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_selectMediaRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_removeMediaRequest = QSharedPointer<QSqlQuery>::create(m_db);

    qDebug() << "Create media request" << m_createMediaRequest->prepare("INSERT INTO media(lib, id) VALUES (:lib, :id)")<< m_createMediaRequest->lastError();
    qDebug() << "Select media request" << m_selectMediaRequest->prepare("SELECT * FROM media WHERE lib=:lib")<< m_selectMediaRequest->lastError();
    qDebug() << "Remove media request" << m_removeMediaRequest->prepare("DELETE FROM media WHERE lib=:lib AND id NOT IN (:ids)")<< m_removeMediaRequest->lastError();
}

void DataSql::initPlaylistRequest()
{
    m_createPlaylistRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_selectPlaylistRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_removePlaylistRequest = QSharedPointer<QSqlQuery>::create(m_db);

    m_selectSmartGroupRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_removeSmartGroupRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_updateSmartGroupRequest = QSharedPointer<QSqlQuery>::create(m_db);

    m_selectSmartRuleRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_removeSmartRuleRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_updateSmartRuleRequest = QSharedPointer<QSqlQuery>::create(m_db);

    m_createMediaPlaylistRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_selectMediaPlaylistRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_removeMediaPlaylistRequest = QSharedPointer<QSqlQuery>::create(m_db);

    qDebug() << "Create playlist request" << m_createPlaylistRequest->prepare("INSERT INTO playlist(lib, id) VALUES (:lib, :id)")<< m_createPlaylistRequest->lastError();
    qDebug() << "Select playlist request" << m_selectPlaylistRequest->prepare("SELECT * FROM playlist WHERE lib=:lib")<< m_selectPlaylistRequest->lastError();
    qDebug() << "Remove playlist request" << m_removePlaylistRequest->prepare("DELETE FROM playlist WHERE id=:id")<< m_removePlaylistRequest->lastError();


    qDebug() << "Select Smart group request" << m_selectSmartGroupRequest->prepare("SELECT * FROM SmartGroup WHERE parent=:parent")<< m_selectSmartGroupRequest->lastError();
    qDebug() << "Remove Smart group request" << m_removeSmartGroupRequest->prepare("DELETE FROM SmartGroup WHERE id=:id")<< m_removeSmartGroupRequest->lastError();
    qDebug() << "Remove Smart group request" << m_updateSmartGroupRequest->prepare("INSERT OR REPLACE INTO SmartGroup (id, op, parent) VALUES (:id, :op, :parent)")<< m_updateSmartGroupRequest->lastError();

    qDebug() << "Select Smart rule request" << m_selectSmartRuleRequest->prepare("SELECT * FROM SmartRule WHERE parent=:parent")<< m_selectSmartRuleRequest->lastError();
    qDebug() << "Remove Smart rule request" << m_removeSmartRuleRequest->prepare("DELETE FROM SmartRule WHERE id=:id")<< m_removeSmartRuleRequest->lastError();
    qDebug() << "Remove Smart rule request" << m_updateSmartRuleRequest->prepare("INSERT OR REPLACE INTO SmartRule (id, op, field, value) VALUES (:id, :op, :field, :value)")<< m_updateSmartRuleRequest->lastError();

    qDebug() << "Create media playlist request" << m_createMediaPlaylistRequest->prepare("INSERT OR REPLACE INTO mediaPlaylist (pl, media, plIndex) VALUES (:pl, :media, :plIndex)")<< m_createMediaPlaylistRequest->lastError();
    qDebug() << "Select media playlist request" << m_selectMediaPlaylistRequest->prepare("SELECT * FROM mediaPlaylist WHERE pl=:pl")<< m_selectMediaPlaylistRequest->lastError();
    qDebug() << "Remove media playlist request" << m_removeMediaPlaylistRequest->prepare("DELETE FROM mediaPlaylist WHERE pl=:pl AND media=:media")<< m_removeMediaPlaylistRequest->lastError();
}

void DataSql::initMetadataRequest()
{
    m_selectMetadataRequest = QSharedPointer<QSqlQuery>::create(m_db);
    //    m_removeMetadataRequest = QSharedPointer<QSqlQuery>::create("", m_db);
    m_updateMetadataRequest = QSharedPointer<QSqlQuery>::create(m_db);

    qDebug()<<"Select Metadata request"<<m_selectMetadataRequest->prepare("SELECT * FROM metadata WHERE id = :id")<<m_selectMetadataRequest->lastError();
    qDebug()<<"Updata Metadata request"<<m_updateMetadataRequest->prepare("INSERT OR REPLACE INTO metadata (id, name, value) VALUES (:id, :name, :value)")<<m_updateMetadataRequest->lastError();
}

void DataSql::initProbeRequest()
{
    m_selectProbeRequest = QSharedPointer<QSqlQuery>::create(m_db);
    m_updateProbeRequest = QSharedPointer<QSqlQuery>::create(m_db);

    qDebug()<<"Select probe request"<<m_selectProbeRequest->prepare("SELECT * FROM probe WHERE lib = :lib")<<m_selectProbeRequest->lastError();
    qDebug()<<"Updata probe request"<<m_updateProbeRequest->prepare("INSERT OR REPLACE INTO probe (lib, lastProbed) VALUES (:lib, :lastProbed)")<<m_updateProbeRequest->lastError();
}

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

        reloadLibrary();

        for(auto it : m_libraries.keys())
            removeLibrary(it.toString());
    }

#include <QSysInfo>
    qDebug()<<QSysInfo::machineUniqueId();
}

void fillMetaData(MetaData& mt, QSharedPointer<QSqlQuery> select)
{
    while(select->next()) {
        auto record = select->record();
        mt.setMetadata(record.value("name").toString(), record.value("value"));
    }
}

void DataSql::reloadMedia(QUuid libId)
{
    m_selectMediaRequest->bindValue(":lib", libId.toString());
    m_selectMediaRequest->exec();

    while(m_selectMediaRequest->next()) {
        auto record = m_selectMediaRequest->record();
        auto media = factory<Media>();
        media->setId(record.value("id").toUuid());

        m_selectMetadataRequest->bindValue(":id", media->id().toString());
        m_selectMetadataRequest->exec();
        fillMetaData(*media, m_selectMetadataRequest);
        m_libraries[libId]->addMedia(media);
    }
}

void DataSql::reloadPlaylist(QUuid libId)
{
    m_selectPlaylistRequest->bindValue(":lib", libId.toString());
    m_selectPlaylistRequest->exec();

    while(m_selectPlaylistRequest->next()) {
        auto record = m_selectPlaylistRequest->record();
        m_selectSmartGroupRequest->bindValue(":id", record.value("id"));
        m_selectSmartGroupRequest->exec();

        auto pl = m_selectSmartGroupRequest->record().count() == 0 ? factory<PlayList>() : factory<SmartPlaylist>();
        pl->setId(record.value("id").toUuid());
        m_selectMetadataRequest->bindValue(":id", pl->id().toString());
        m_selectMetadataRequest->exec();
        fillMetaData(*pl, m_selectMetadataRequest);

        while(m_selectSmartGroupRequest->next()) {
            auto groupRecord = m_selectSmartGroupRequest->record();
            auto group = factory<SmartGroup>();
            group->setMetadata("id", groupRecord.value("id").toUuid());
            group->setOp(groupRecord.value("op").value<AbstractRule::Op>());
            pl.dynamicCast<SmartPlaylist>()->setRules(group);

            m_selectSmartRuleRequest->bindValue(":parent", group->id());
            m_selectSmartRuleRequest->exec();

            while(m_selectSmartRuleRequest->next()) {
                auto ruleRecord = m_selectSmartRuleRequest->record();
                auto rule = group->add().dynamicCast<SmartRule>();
                rule->setMetadata("id", ruleRecord.value(("id")));
                rule->setOp(ruleRecord.value("op").value<AbstractRule::Op>());
                rule->setField(ruleRecord.value("field").toString());
                rule->setValue(ruleRecord.value("value"));
            }
        }
    }
}

void DataSql::reloadLibrary()
{
    m_libraries.clear();
    m_selectLibraryRequest->exec();

    while(m_selectLibraryRequest->next()) {
        auto lib = factory<Library>();
        lib->setId(m_selectLibraryRequest->record().value("id").toUuid());

        m_libraries[lib->id()] = lib;
        m_selectMetadataRequest->bindValue(":id", lib->id().toString());
        m_selectMetadataRequest->exec();

        fillMetaData(*lib, m_selectMetadataRequest);

        m_selectProbeRequest->bindValue(":lib", lib->id().toString());

        while(m_selectProbeRequest->next()) {
            lib->probe()->setLastProbed(m_selectProbeRequest->record().value("lastProbed").toDateTime());
        }

        reloadMedia(lib->id());
    }

    emit librariesChanged();
}

template<class T>
bool remove (T container, QSharedPointer<QSqlQuery> query, QUuid lib)
{
    query->bindValue(":lib", lib);
    auto keys = container.keys();
    QStringList keysString;
    for(auto it: keys) {
        keysString<<it.toString();
    }

    query->bindValue(":ids", keysString.join(","));
    return query->exec();
}

bool DataSql::deleteMedia(QUuid lib)
{
    auto ret = remove(m_libraries[lib]->medias(), m_removeMediaRequest , lib);
    return ret;
}

bool DataSql::deletePlaylist(QUuid lib)
{
    auto pl = m_libraries[lib]->allPlaylist();
    auto ret = remove(pl, m_removeMediaRequest , lib);
    return ret;
}

bool DataSql::deleteSmartGroup(QUuid id)
{
    m_removeSmartGroupRequest->bindValue(":id", id);
    auto ret = m_removeSmartGroupRequest->exec();
    return ret;
}

bool DataSql::deleteSmartRule(QUuid id)
{
    m_removeSmartRuleRequest->bindValue(":id", id);
    auto ret =  m_removeSmartRuleRequest->exec();
    return ret;
}

bool DataSql::insertMedia(MediaPointer) {return false;}
bool DataSql::insertPlaylist(PlaylistPointer) {return false;}
bool DataSql::insertSmartGroup(SmartGroupPointer) {return false;}
bool DataSql::insertSmartRule(SmartRulePointer) {return false;}

bool DataSql::updateMedia(QUuid) {return false;}
bool DataSql::updatePlaylist(QUuid) {return false;}
bool DataSql::updateSmartGroup(QUuid) {return false;}
bool DataSql::updateSmartRule(QUuid) {return false;}
