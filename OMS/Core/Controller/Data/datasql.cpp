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

QMap<QUuid, LibraryPointer> DataSql::selectLibrary() const
{
    auto ret = QMap<QUuid, LibraryPointer>();
    return m_libraries;
}

bool DataSql::createLibrary(QString name, MediaPlayerGlobal::MediaRole role)
{
    return false;
}

bool DataSql::removeLibrary(QString id)
{
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
