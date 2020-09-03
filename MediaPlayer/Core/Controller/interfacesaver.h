#ifndef INTERFACESAVER_H
#define INTERFACESAVER_H

#include <QObject>
#include "Model/library.h"

class InterfaceSaver: public QObject
{
    
   Q_OBJECT
    
private:
    
public:
    InterfaceSaver() = default;
    InterfaceSaver(const InterfaceSaver&) = default;
    virtual ~InterfaceSaver() = default;

    virtual void init() = 0;

public slots:
    virtual QMap<QUuid, LibraryPointer> selectLibrary(QUuid = QUuid()) const = 0;
    virtual LibraryPointer createLibrary(QString) = 0;
    virtual bool removeLibrary(LibraryPointer) = 0;
    virtual bool updateLibrary(LibraryPointer) = 0;
};

#endif // INTERFACESAVER_H

