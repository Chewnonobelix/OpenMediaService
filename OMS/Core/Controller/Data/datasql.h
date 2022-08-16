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

    QSharedPointer<QSqlQuery> m_createMediaRequest;
    QSharedPointer<QSqlQuery> m_selectMediaRequest;
    QSharedPointer<QSqlQuery> m_removeMediaRequest;

    QSharedPointer<QSqlQuery> m_createPlaylistRequest;
    QSharedPointer<QSqlQuery> m_selectPlaylistRequest;
    QSharedPointer<QSqlQuery> m_removePlaylistRequest;
    //    QSharedPointer<QSqlQuery> m_updatePlaylistRequest;

    QSharedPointer<QSqlQuery> m_selectSmartGroupRequest;
    QSharedPointer<QSqlQuery> m_removeSmartGroupRequest;
    QSharedPointer<QSqlQuery> m_updateSmartGroupRequest;

    QSharedPointer<QSqlQuery> m_selectSmartRuleRequest;
    QSharedPointer<QSqlQuery> m_removeSmartRuleRequest;
    QSharedPointer<QSqlQuery> m_updateSmartRuleRequest;

    QSharedPointer<QSqlQuery> m_createMediaPlaylistRequest;
    QSharedPointer<QSqlQuery> m_selectMediaPlaylistRequest;
    QSharedPointer<QSqlQuery> m_removeMediaPlaylistRequest;

    QSharedPointer<QSqlQuery> m_selectMetadataRequest;
    QSharedPointer<QSqlQuery> m_updateMetadataRequest;
    //    QSharedPointer<QSqlQuery> m_removeMetadataRequest;

    //    QSqlQuery m_createProbeRequest;
    QSharedPointer<QSqlQuery> m_selectProbeRequest;
    QSharedPointer<QSqlQuery> m_updateProbeRequest;

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

    void reloadMedia(QUuid);
    void reloadPlaylist(QUuid);
    void reloadLibrary();

    void removeMedia(QUuid);
    void removePlaylist(QUuid);
    void removeSmartGroup(QUuid);
    void removeSmartRule(QUuid);

    void createMedia(MediaPointer);
    void createPlaylist(PlaylistPointer);
    void createSmartGroup(SmartGroupPointer);
    void createSmartRule(SmartRule);

    void updateMedia(MediaPointer);
    void updatePlaylist(PlaylistPointer);
    void updateSmartGroup(SmartGroupPointer);
    void updateSmartRule(SmartRule);

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

