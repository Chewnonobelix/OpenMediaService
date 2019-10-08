#ifndef CONTROLLERMAIN_H
#define CONTROLLERMAIN_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QCoreApplication>
#include "controllerlibrary.h"


class ControllerMain
{
private:    
    QQmlApplicationEngine m_engine;
    QObject* m_root;
    
    ControllerLibrary m_library;
    QMap<QString, MediaPlayerGlobal::MediaRole> m_tabWindows;
    
public:
    ControllerMain();
    
};

#endif // CONTROLLERMAIN_H
