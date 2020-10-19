#ifndef CONTROLLERMAIN_H
#define CONTROLLERMAIN_H

#include "../DataModel/librarydatamodel.h"
#include "../Data/DataXml.h"
#include "abstractcontroller.h"
#include "controllerlibrary.h"
#include <QCoreApplication>
#include <QObject>
#include <QQmlContext>

class ControllerMain : public AbstractController
{
    Q_OBJECT
    Q_DISABLE_COPY(ControllerMain)
private:
    ControllerLibrary m_libraries;

    QQmlApplicationEngine &engine();

public:
    ControllerMain();
    ~ControllerMain() = default;

    void exec();

};


#endif // CONTROLLERMAIN_H
