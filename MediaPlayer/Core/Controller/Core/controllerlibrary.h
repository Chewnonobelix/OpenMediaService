#pragma once

#include <Controller/Core/abstractcontroller.h>
#include <Controller/DataModel/playlistmodel.h>

#include <Model/library.h>

class ControllerLibrary : public AbstractController {
	Q_OBJECT
	Q_DISABLE_COPY(ControllerLibrary)

	Q_PROPERTY(PlaylistModel *playlist READ playlist)
	Q_PROPERTY(Library *currentLibrary READ library NOTIFY libraryChanged)

private:
	LibraryPointer m_current = nullptr;
	QPointer<PlaylistModel> m_playlist = new PlaylistModel();
	int m_currentIndex = -1;

	Library *library() const;

public:
	ControllerLibrary() = default;
	~ControllerLibrary() = default;

	void exec() override;

	PlaylistModel *playlist() const;

	Q_INVOKABLE void setCurrentLibrary(QString);

	Q_INVOKABLE void open();

	Q_INVOKABLE void addSourceDir(QString);
	Q_INVOKABLE void removeSourceDir(QString);
	Q_INVOKABLE void addPlaylist(bool = false);
	Q_INVOKABLE void removePlaylist(QString);

signals:
	void libraryChanged();
};
