#pragma once

#include <QObject>

#include <liveqmlengine.h>

#include <mediaplayercore_global.h>

#include <Controller/Data/interfacesaver.h>
#include <Controller/DataModel/librarydatamodel.h>
#include <Controller/DataModel/playlistmodel.h>
#include <Controller/Plugins/pluginmanager.h>

class MEDIAPLAYERCORE_EXPORT AbstractController : public QObject {
	Q_OBJECT

public:
	AbstractController();
	AbstractController(const AbstractController &);
	~AbstractController() = default;

	virtual void exec() = 0;

	static InterfaceSaver *db();
	static void setDb(QString);
	static PluginManager m_manager;
	static QPointer<LibraryDataModel> m_librariesModel;
	static QPointer<PlaylistModel> m_playlistModel;

signals:

protected:
	static QPointer<LiveQmlEngine> m_engine;

private:
	static InterfaceSaver *m_db;
	static QThread *m_dbThread;
};
