#pragma once

#include <QCoreApplication>
#include <QObject>
#include <QQmlContext>

#include <mediaplayercore_global.h>

#include "../Data/datajson.h"
#include "../Data/dataxml.h"
#include "../DataModel/librarydatamodel.h"
#include "abstractcontroller.h"
#include "controllerlibrary.h"
#include <Controller/Plugins/PluginManager.hpp>

class MEDIAPLAYERCORE_EXPORT ControllerMain : public AbstractController {
	Q_OBJECT
	Q_DISABLE_COPY(ControllerMain)
private:
	QPointer<ControllerLibrary> m_libraries;

	QQmlApplicationEngine &engine();

public:
	ControllerMain();
	~ControllerMain() = default;

	void exec();

public slots:
	void onLibraryChanged();

signals:
	void playlistDisplay(QString);
	void playerDisplay(QString);
};
