#ifndef CONTROLLERLIBRARY_H
#define CONTROLLERLIBRARY_H

#include <QObject>
#include <QList>
#include <QSharedPointer>
#include <QPair>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include "interfacesaver.h"
#include "Model/library.h"

class ControllerLibrary: public QObject
{
    Q_OBJECT
    
private:
    void open(QString);
    
public:
    ControllerLibrary();
    ~ControllerLibrary();
    
    void probeAll();
    bool addLibrary(QString, MediaRole);
    
    QList<QPair<LibraryPointer, QSharedPointer<InterfaceSaver>>> m_libs;
    
};

#endif // CONTROLLERLIBRARY_H
