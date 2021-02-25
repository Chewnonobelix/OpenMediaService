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
	Q_PROPERTY(int modelIndex READ modelIndex WRITE setModelIndex NOTIFY
								 modelIndexChanged)

	Q_PROPERTY(bool isActive READ isActive WRITE setActive NOTIFY isActiveChanged)
	Q_PROPERTY(PlaylistModel *playlist READ playlist)

private:
	static QMap<ControllerLibrary *, bool> m_actives;
	bool m_isActive = false;

	LibraryPointer m_currentLibrary;
	PlaylistModel m_playlist;
	int m_modelIndex = -1;

public:
	ControllerLibrary();
	ControllerLibrary(const ControllerLibrary &);
	~ControllerLibrary();

	void exec() override;

	Library *currentLibrary() const;
	PlaylistModel *playlist();

	Q_INVOKABLE void open();

	Q_INVOKABLE void addSourceDir(QString);
	Q_INVOKABLE void removeSourceDir(QString);
	Q_INVOKABLE void addPlaylist(bool = false);
	Q_INVOKABLE void removePlaylist(QString);

	int modelIndex() const;
	void setModelIndex(int);

	Q_INVOKABLE void setCurrentLibrary(QString);

	bool isActive() const;
	void setActive(bool);

	static ControllerLibrary *active();

signals:
	void currentLibraryChanged();
	void modelIndexChanged();
	void isActiveChanged();

public slots:
	void onCurrentModelChanged(LibraryPointer);
	void onCurrentPlaylistChanged(PlaylistPointer);
	void onLibraryChanged();
};
