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

    QMap<QUuid, LibraryPointer> selectLibrary(QUuid = QUuid()) const;
    LibraryPointer createLibrary();
    bool removeLibrary(LibraryPointer);
    bool updateLibrary(LibraryPointer);
    
    virtual void init() = 0;

public slots:    
    
};

#endif // INTERFACESAVER_H

