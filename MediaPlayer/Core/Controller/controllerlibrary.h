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
    QMap<QString, QPair<LibraryPointer, QSharedPointer<InterfaceSaver>>> m_libs;
    
public:
    ControllerLibrary();
    ~ControllerLibrary();
    
    void probeAll();
    bool addLibrary(QString, MediaRole);
    
    QStringList librariesName() const;
    QPair<LibraryPointer, QSharedPointer<InterfaceSaver>> library(QString);
    QMap<QString, QPair<LibraryPointer, QSharedPointer<InterfaceSaver>>> libraries() const;
};

#endif // CONTROLLERLIBRARY_H
