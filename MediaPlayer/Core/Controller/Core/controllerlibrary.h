#pragma once

#include <Controller/Core/abstractcontroller.h>
#include <Controller/DataModel/playlistmodel.h>
#include <Controller/Core/tabmanager.h>

#include <Model/library.h>

class ControllerLibrary : public AbstractController {
	Q_OBJECT
	Q_DISABLE_COPY(ControllerLibrary)

	Q_PROPERTY(PlaylistModel *playlist READ playlist)
    Q_PROPERTY(Library *currentLibrary READ library NOTIFY libraryChanged)
	Q_PROPERTY(QString id READ id CONSTANT)

private:
	LibraryPointer m_current = nullptr;
    PlaylistModel m_playlist;

	QUuid m_id = QUuid::createUuid();

    QMap<QUuid, QSharedPointer<InterfacePlugins>> m_plugins;

	Library *library() const;
    PlaylistModel *playlist() ;

public:
	ControllerLibrary() = default;
    ~ControllerLibrary() = default;

	Q_INVOKABLE void exec() override;

    Q_INVOKABLE void setCurrentLibrary(LibraryPointer);

	Q_INVOKABLE void open();

	Q_INVOKABLE void addSourceDir(QString);
	Q_INVOKABLE void removeSourceDir(QString);
	Q_INVOKABLE void addPlaylist(bool = false);
	Q_INVOKABLE void removePlaylist(QString);

    QString id() const;

public:
    Q_INVOKABLE void setPlaylistIndex(QString, int);
    Q_INVOKABLE QQmlComponent* playerComp(QString);
    Q_INVOKABLE QQmlComponent* playlistComp(QString = "");

public slots:
	void onUpdateLibrary();
    void onCurrentPlaylistChanged();
    void onPlay(MediaPointer);

signals:
	void libraryChanged();
    void play(QUuid, Media*);
};
