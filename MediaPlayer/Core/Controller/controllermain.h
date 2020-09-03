#ifndef CONTROLLERMAIN_H
#define CONTROLLERMAIN_H

#include "abstractcontroller.h"
#include <QCoreApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class ControllerMain : public AbstractController
{
    Q_OBJECT

private:
    QQmlApplicationEngine m_engine;

    QQmlApplicationEngine &engine();

public:
    ControllerMain() = default;
    ControllerMain(const ControllerMain &);
    ~ControllerMain() = default;

    void exec();
};

Q_DECLARE_METATYPE(ControllerMain)

#endif // CONTROLLERMAIN_H
