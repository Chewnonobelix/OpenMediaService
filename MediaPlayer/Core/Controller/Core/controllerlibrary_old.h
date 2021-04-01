#pragma once
#include <QQmlContext>
#include <QtCore/qglobal.h>

#include "../DataModel/librarydatamodel.h"
#include "../DataModel/playlistmodel.h"

#include "abstractcontroller.h"
#include "liveqmlengine.h"
#include <Controller/Plugins/interfaceplugins.h>
#include <mediaplayercore_global.h>

class MEDIAPLAYERCORE_EXPORT ControllerLibrary_old : public AbstractController {
	Q_OBJECT

	Q_PROPERTY(
			Library *currentLibrary READ currentLibrary NOTIFY currentLibraryChanged)
	Q_PROPERTY(int modelIndex READ modelIndex WRITE setModelIndex NOTIFY
								 modelIndexChanged)

	Q_PROPERTY(bool isActive READ isActive WRITE setActive NOTIFY isActiveChanged)
	Q_PROPERTY(PlaylistModel *playlist READ playlist)

private:
	static QMap<ControllerLibrary_old *, bool> m_actives;
	bool m_isActive = false;

	LibraryPointer m_currentLibrary;
	int m_modelIndex = -1;
	QSharedPointer<InterfacePlugins> m_plugins;
	PlaylistModel m_playlist;

public:
	ControllerLibrary_old();
	ControllerLibrary_old(const ControllerLibrary_old &);
	~ControllerLibrary_old();

	void exec() /*override*/;

	Library *currentLibrary() const;

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
	static ControllerLibrary_old *active();
	QSharedPointer<InterfacePlugins> plugins();
	PlaylistModel *playlist();

signals:
	void currentLibraryChanged();
	void modelIndexChanged();
	void isActiveChanged();

public slots:
	void onCurrentModelChanged(LibraryPointer);
	void onCurrentPlaylistChanged(PlaylistPointer);
	void onLibraryChanged();
};
