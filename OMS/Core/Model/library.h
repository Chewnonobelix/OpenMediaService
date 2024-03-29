#pragma once

#include <QMap>
#include <QObject>
#include <QSharedPointer>

#include <mediaplayercore_global.h>

#include "libraryprobe.h"
#include "media.h"
#include "metadata.h"
#include "playlist.h"
#include "smartplaylist.h"

using namespace MediaPlayerGlobal;

class Library;

typedef QSharedPointer<Library> LibraryPointer;

class MEDIAPLAYERCORE_EXPORT Library : public QObject, public MetaData, public QEnableSharedFromThis<Library> {
	Q_OBJECT

	Q_PROPERTY(QUuid id READ id CONSTANT)
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(MediaPlayerGlobal::MediaRole role READ role CONSTANT)
	Q_PROPERTY(bool isShared READ isShared WRITE setShared NOTIFY isSharedChanged)
	Q_PROPERTY(QStringList sourceDir READ sourceDir NOTIFY sourceDirChanged)
	Q_PROPERTY(int mediaCount READ mediaCount NOTIFY mediasChanged)
	Q_PROPERTY(LibraryProbe *probe READ probe CONSTANT)
	Q_PROPERTY(int playlistCount READ playlistCount NOTIFY playlistCountChanged)

private:
	LibraryProbe m_probe;
    QMap<MD5, QUuid> m_pool;
    QMap<QUuid, MediaPointer> m_medias;
	QMap<QUuid, SmartPlaylistPointer> m_smartPlaylist;
	QMap<QUuid, PlaylistPointer> m_playlist;

	void set();

    QPointer<QThread> m_replacer = nullptr;


    QJsonArray jsonTagList(QList<MediaPlayerGlobal::Tag>) const;
    QList<MediaPlayerGlobal::Tag> fromjsonTagList(QJsonArray) const;

    void connectLibrary(LibraryPointer);
public:
	Library();
	using MetaData::MetaData;
	Library(const Library &);
	Library(QJsonObject &);
    ~Library() = default;

	Library &operator=(const Library &);
	operator QJsonObject() const override;

	friend bool operator<(LibraryPointer, LibraryPointer);

	QUuid id() const;
    bool setId(QUuid);

	QString name() const;
    bool setName(QString);

	MediaPlayerGlobal::MediaRole role() const;
    bool setRole(MediaPlayerGlobal::MediaRole);

	bool isShared() const;
    bool setShared(bool);

	Q_INVOKABLE QStringList sourceDir() const;

	int mediaCount() const;
    int playlistCount() const;

	LibraryProbe *probe();

    QList<MediaPlayerGlobal::Tag> tags() const;
    void addTag(MediaPlayerGlobal::Tag);
    bool editTag(MediaPlayerGlobal::Tag);
    bool removeTag(MediaPlayerGlobal::Tag);

    void setTagList(QStringList);
    QStringList tagList() const;

public slots:
    Q_INVOKABLE bool scan();

	Q_INVOKABLE bool addMedia(MediaPointer);
	Q_INVOKABLE bool removeMedia(QString);
    Q_INVOKABLE QMap<QUuid, MediaPointer> medias(QString = "");

	Q_INVOKABLE bool addSourceDir(QString);
	Q_INVOKABLE bool removeSourceDir(QString);

	Q_INVOKABLE bool addSmartPlaylist(SmartPlaylistPointer);
	Q_INVOKABLE bool removeSmartPlaylist(QString);
	Q_INVOKABLE QMap<QUuid, SmartPlaylistPointer> smartPlaylist(QString = "");

	Q_INVOKABLE bool addPlaylist(PlaylistPointer);
	Q_INVOKABLE bool removePlaylist(QString);
	Q_INVOKABLE QMap<QUuid, PlaylistPointer> playlist(QString = "");

    Q_INVOKABLE QList<PlayList*> playlistList() const;
    QMap<QUuid, PlaylistPointer> allPlaylist() const;

    Q_INVOKABLE bool addToPlaylist(QString, QString);

	void onProbedChanged();
	void onMediaChanged();
    void onSmartPlaylistChanged();

signals:
	void nameChanged();
	void isSharedChanged();
	void sourceDirChanged();
	void mediasChanged(MediaPointer = MediaPointer());
	void lastUpdateChanged();
	void playlistCountChanged();

	void libraryChanged();
};

Q_DECLARE_METATYPE(Library)
