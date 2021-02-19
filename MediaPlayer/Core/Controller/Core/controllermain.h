#pragma once

#include <QCoreApplication>
#include <QObject>
#include <QQmlContext>

#include <mediaplayercore_global.h>

#include "../Data/datajson.h"
#include "../Data/dataxml.h"
#include "abstractcontroller.h"
#include "controllerlibrary.h"
#include <Controller/Plugins/pluginmanager.h>

class MEDIAPLAYERCORE_EXPORT ControllerMain : public AbstractController {
	Q_OBJECT
	Q_DISABLE_COPY(ControllerMain)

private:
	int m_currentTab = 0;

	QQmlApplicationEngine &engine();

public:
	ControllerMain();
	~ControllerMain() = default;

	void exec();

	Q_INVOKABLE void onTabChanged(int);

public slots:
	void onLibraryChanged();
	void addTab();

signals:
	void playlistDisplay(QString);
	void playerDisplay(QString, int);
};
