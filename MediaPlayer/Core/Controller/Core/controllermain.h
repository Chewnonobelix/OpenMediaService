#pragma once

#include <QCoreApplication>
#include <QObject>
#include <QQmlContext>

#include "../Data/dataxml.h"
#include "../DataModel/librarydatamodel.h"
#include "abstractcontroller.h"
#include "controllerlibrary.h"

class ControllerMain : public AbstractController {
	Q_OBJECT
	Q_DISABLE_COPY(ControllerMain)
private:
	QPointer<ControllerLibrary> m_libraries;

	QQmlApplicationEngine &engine();

public:
	ControllerMain();
	~ControllerMain() = default;

	void exec();
};
