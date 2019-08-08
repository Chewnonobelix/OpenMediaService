#ifndef CONTROLLERLIBRARY_H
#define CONTROLLERLIBRARY_H

#include <QObject>
#include <QList>
#include <QSharedPointer>
#include <QPair>
#include <QDebug>
#include "interfacesaver.h"
#include "Model/library.h"

class ControllerLibrary: public QObject
{
    Q_OBJECT
    QList<QPair<LibraryPointer, QSharedPointer<InterfaceSaver>>> m_libs;
    
public:
    ControllerLibrary();
    ~ControllerLibrary();
    
    void probeAll();
    bool addLibrary(QString, MediaRole);
};

#endif // CONTROLLERLIBRARY_H
