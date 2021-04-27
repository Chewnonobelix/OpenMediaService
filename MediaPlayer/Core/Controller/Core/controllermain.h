#pragma once

#include <QCoreApplication>
#include <QObject>
#include <QQmlComponent>
#include <QQmlContext>

#include <mediaplayercore_global.h>

#include "../Data/datajson.h"
#include "../Data/dataxml.h"
#include "abstractcontroller.h"
#include "controllerlibrary.h"
#include "tabmanager.h"
#include <Controller/Plugins/pluginmanager.h>
#include "controllersettings.h"

class MEDIAPLAYERCORE_EXPORT ControllerMain : public AbstractController {
	Q_OBJECT
	Q_DISABLE_COPY(ControllerMain)

private:
	int m_currentTab = 0;

	QQmlApplicationEngine &engine();
	TabManager m_tabsManager;
    ControllerSettings m_settings;

public:
	ControllerMain();
	~ControllerMain() = default;

	void exec();

public slots:

signals:
	void playlistDisplay(QQmlComponent *);
	void componentChanged(QQmlComponent *);
};
