#pragma once

#include <QMap>
#include <QObject>
#include <QSharedPointer>

#include "libraryprobe.h"
#include "media.h"
#include "metadata.h"
#include "playlist.h"
#include "smartplaylist.h"

using namespace MediaPlayerGlobal;

class Library;

typedef QSharedPointer<Library> LibraryPointer;

class Library : public QObject, public MetaData {
	Q_OBJECT

	Q_PROPERTY(QUuid id READ id CONSTANT)
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(MediaPlayerGlobal::MediaRole role READ role CONSTANT)
	Q_PROPERTY(bool isShared READ isShared WRITE setShared NOTIFY isSharedChanged)
	Q_PROPERTY(QDateTime lastProbed READ lastProbed WRITE setLastProbed NOTIFY
								 lastProbedChanged)
	Q_PROPERTY(QDateTime lastUpdate READ lastUpdate WRITE setLastUpdate NOTIFY
								 lastUpdateChanged)
	Q_PROPERTY(QStringList sourceDir READ sourceDir NOTIFY sourceDirChanged)
	Q_PROPERTY(int mediaCount READ mediaCount NOTIFY mediasChanged)
	Q_PROPERTY(LibraryProbe *probe READ probe CONSTANT)
	Q_PROPERTY(int playlistCount READ playlistCount NOTIFY playlistCountChanged)
private:
	LibraryProbe m_probe;
	QMap<MD5, MediaPointer> m_medias;
	QMap<QUuid, SmartPlaylistPointer> m_smartPlaylist;
	QMap<QUuid, PlaylistPointer> m_playlist;

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
	void setId(QUuid);
	QString name() const;
	void setName(QString);
	MediaPlayerGlobal::MediaRole role() const;
	void setRole(MediaPlayerGlobal::MediaRole);
	bool isShared() const;
	void setShared(bool);
	QDateTime lastProbed() const;
	void setLastProbed(QDateTime);
	Q_INVOKABLE QStringList sourceDir() const;
	QDateTime lastUpdate() const;
	void setLastUpdate(QDateTime);
	int mediaCount() const;
	LibraryProbe *probe();
	int playlistCount() const;

public slots:
	Q_INVOKABLE void scan();
	Q_INVOKABLE bool addNMedia(QString, MD5 = "");
	Q_INVOKABLE bool addMedia(MediaPointer);
	Q_INVOKABLE bool removeMedia(QString);
	Q_INVOKABLE QMap<MD5, MediaPointer> medias(MD5 = "") const;

	Q_INVOKABLE bool addSourceDir(QString);
	Q_INVOKABLE bool removeSourceDir(QString);

	Q_INVOKABLE bool addSmartPlaylist(SmartPlaylistPointer);
	Q_INVOKABLE bool removeSmartPlaylist(QString);
	Q_INVOKABLE QMap<QUuid, SmartPlaylistPointer> smartPlaylist(QString = "");

	Q_INVOKABLE bool addPlaylist(PlaylistPointer);
	Q_INVOKABLE bool removePlaylist(QString);
	Q_INVOKABLE QMap<QUuid, PlaylistPointer> playlist(QString = "");

	void onProbedChanged();

signals:
	void nameChanged();
	void isSharedChanged();
	void lastProbedChanged();
	void sourceDirChanged();
	void mediasChanged(MediaPointer = MediaPointer());
	void lastUpdateChanged();
	void playlistCountChanged();
};

Q_DECLARE_METATYPE(Library)
