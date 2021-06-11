#pragma once

#include <QObject>

#include <liveqmlengine.h>

#include <mediaplayercore_global.h>

#include <Controller/Data/interfacesaver.h>
#include <Controller/DataModel/playlistmodel.h>
#include <Controller/Plugins/pluginmanager.h>
#include "controllersettings.h"
#include <Controller/Core/tabwrapper.h>

class MEDIAPLAYERCORE_EXPORT AbstractController : public QObject {
	Q_OBJECT
    Q_DISABLE_COPY(AbstractController)

public:
	AbstractController();
    ~AbstractController() = default;

	virtual void exec() = 0;

	static InterfaceSaver *db();
	static void setDb(QString);
	static PluginManager s_manager;
    static QPointer<ControllerSettings> s_settings;
    static QPointer<TabWrapper> s_tabWrapper;

signals:

protected:
	static QPointer<LiveQmlEngine> s_engine;

private:
	static InterfaceSaver *s_db;
	static QThread *s_dbThread;
};
