#ifndef CONTROLLERMAIN_H
#define CONTROLLERMAIN_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QCoreApplication>


class ControllerMain
{
private:    
    QQmlApplicationEngine m_engine;
    QObject* m_root;
    
    
public:
    ControllerMain() = default;
    ~ControllerMain() = default;
    
};

#endif // CONTROLLERMAIN_H
