#ifndef CONTROLLERMAIN_H
#define CONTROLLERMAIN_H

#include "DataXml.h"
#include "abstractcontroller.h"
#include "liveqmlengine.h"
#include <QCoreApplication>
#include <QObject>
#include <QQmlContext>
class ControllerMain : public AbstractController
{
    Q_OBJECT
    Q_DISABLE_COPY(ControllerMain)
private:
    LiveQmlEngine m_engine;

    QQmlApplicationEngine &engine();

public:
    ControllerMain();
    ~ControllerMain() = default;

    void exec();
};


#endif // CONTROLLERMAIN_H
