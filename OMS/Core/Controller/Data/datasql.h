#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <Controller/Data/interfacesaver.h>

#include <Model/library.h>
#include <Model/media.h>
#include <Model/smartplaylist.h>

class DataSql: public InterfaceSaver
{
private:
    QMap<QUuid, LibraryPointer> m_libraries;
    QSqlDatabase m_db;

    QSharedPointer<QSqlQuery> m_createLibraryRequest;
    QSharedPointer<QSqlQuery> m_selectLibraryRequest;
    QSharedPointer<QSqlQuery> m_removeLibraryRequest;

    QSqlQuery m_createMediaRequest;
    QSqlQuery m_selectMediaRequest;
    QSqlQuery m_removeMediaRequest;
    QSqlQuery m_updateMediaRequest;

    QSharedPointer<QSqlQuery> m_createPlaylistRequest;
    QSharedPointer<QSqlQuery> m_selectPlaylistRequest;
    QSharedPointer<QSqlQuery> m_removePlaylistRequest;
    QSharedPointer<QSqlQuery> m_updatePlaylistRequest;

//    QSharedPointer<QSqlQuery> m_createMetadataRequest;
//    QSharedPointer<QSqlQuery> m_selectMetadataRequest;
//    QSharedPointer<QSqlQuery> m_removeMetadataRequest;
    QSharedPointer<QSqlQuery> m_updateMetadataRequest;

    QSqlQuery m_createProbeRequest;
    QSqlQuery m_selectProbeRequest;
    QSqlQuery m_removeProbeRequest;
    QSqlQuery m_updateProbeRequest;

    QSqlQuery m_createSourceDirRequest;
    QSqlQuery m_selectSourceDirRequest;
    QSqlQuery m_removeSourceDirRequest;
    QSqlQuery m_updateSourceDirRequest;


    void initLibRequest();
    void initMediaRequest();
    void initPlaylistRequest();
    void initMetadataRequest();
    void initProbeRequest();
    void initSourceDirRequest();

    bool updateMetadata(QUuid,QString, QVariant);

public:
    DataSql() = default;
    DataSql(const DataSql &);
    ~DataSql() override;

    virtual void init() override;

public slots:
    QMap<QUuid, LibraryPointer> selectLibrary() const override;
    bool createLibrary(QString, MediaPlayerGlobal::MediaRole) override;
    bool removeLibrary(QString) override;
    bool updateLibrary(LibraryPointer) override;
};

