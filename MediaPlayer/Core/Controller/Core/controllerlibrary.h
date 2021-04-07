#pragma once

#include <Controller/Core/abstractcontroller.h>
#include <Controller/DataModel/playlistmodel.h>

#include <Model/library.h>

class ControllerLibrary : public AbstractController {
	Q_OBJECT
	Q_DISABLE_COPY(ControllerLibrary)

	Q_PROPERTY(PlaylistModel *playlist READ playlist)
	Q_PROPERTY(Library *currentLibrary READ library NOTIFY libraryChanged)
    Q_PROPERTY(QQmlComponent* playlistComponent READ playlistComponent NOTIFY playlistComponentChanged)
    Q_PROPERTY(QQmlComponent* playerComponent READ playerComponent NOTIFY playerComponentChanged)

private:
	LibraryPointer m_current = nullptr;
	QPointer<PlaylistModel> m_playlist = new PlaylistModel();
	int m_currentIndex = -1;

	Library *library() const;
    PlaylistModel *playlist() const;
    QSharedPointer<InterfacePlugins> m_plugin;
    QQmlComponent* playlistComponent() const;
    QQmlComponent* playerComponent() const;

public:
	ControllerLibrary() = default;
	~ControllerLibrary() = default;

    Q_INVOKABLE void exec() override;


	Q_INVOKABLE void setCurrentLibrary(QString);

	Q_INVOKABLE void open();

	Q_INVOKABLE void addSourceDir(QString);
	Q_INVOKABLE void removeSourceDir(QString);
	Q_INVOKABLE void addPlaylist(bool = false);
	Q_INVOKABLE void removePlaylist(QString);

public slots:
    void onUpdateLibrary();
    void onCurrentPlaylistChanged(PlaylistPointer);

signals:
	void libraryChanged();
    void playlistComponentChanged();
    void playerComponentChanged();
};
