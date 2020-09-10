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
    InterfaceSaver(const InterfaceSaver &);
    virtual ~InterfaceSaver() = default;

    virtual void init() = 0;

public slots:
    virtual QMap<QUuid, LibraryPointer> selectLibrary() const = 0;
    virtual bool createLibrary(QString, MediaPlayerGlobal::MediaRole) = 0;
    virtual bool removeLibrary(LibraryPointer) = 0;
    virtual bool updateLibrary(LibraryPointer) = 0;

signals:
    void addLibrary(LibraryPointer);
};

#endif // INTERFACESAVER_H

