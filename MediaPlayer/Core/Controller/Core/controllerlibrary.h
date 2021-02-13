#pragma once
#include <QQmlContext>
#include <QtCore/qglobal.h>

#include "../DataModel/librarydatamodel.h"
#include "../DataModel/playlistmodel.h"

#include "abstractcontroller.h"
#include "liveqmlengine.h"

class ControllerLibrary : public AbstractController {
	Q_OBJECT
	Q_PROPERTY(
			Library *currentLibrary READ currentLibrary NOTIFY currentLibraryChanged)

private:
	LibraryPointer m_currentLibrary;
	LibraryDataModel m_librariesModel;
	PlaylistModel m_playlistModel;

public:
	ControllerLibrary();
	ControllerLibrary(const ControllerLibrary &);
	~ControllerLibrary() = default;

	void exec() override;

	Library *currentLibrary() const;

	Q_INVOKABLE void open();

	Q_INVOKABLE void addSourceDir(QString);
	Q_INVOKABLE void removeSourceDir(QString);
	Q_INVOKABLE void addPlaylist(bool = false);
	Q_INVOKABLE void removePlaylist(QString);

signals:
	void currentLibraryChanged();

public slots:
	void onCurrentModelChanged(LibraryPointer);
	void onCurrentPlaylistChanged();
	void onLibraryChanged();
};
