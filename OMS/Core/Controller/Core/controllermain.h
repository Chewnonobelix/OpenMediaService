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
#include <Controller/DataModel/librarydatamodel.h>
#include <Controller/DataModel/smartmodel.h>

Q_DECLARE_LOGGING_CATEGORY(mainregister)
Q_DECLARE_LOGGING_CATEGORY(mainlog)

class MEDIAPLAYERCORE_EXPORT ControllerMain : public AbstractController {
	Q_OBJECT
	Q_DISABLE_COPY(ControllerMain)

private:
	int m_currentTab = 0;

	QQmlApplicationEngine &engine();
    QPointer<LibraryDataModel> m_librariesModel;

public:
	ControllerMain();
	~ControllerMain() = default;

	void exec();

public slots:
    void onDbChanged();

signals:
	void playlistDisplay(QQmlComponent *);
	void componentChanged(QQmlComponent *);
};
