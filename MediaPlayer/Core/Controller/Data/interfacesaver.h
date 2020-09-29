#ifndef INTERFACESAVER_H
#define INTERFACESAVER_H

#include "../../Model/library.h"
#include <QObject>

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
    virtual bool createLibrary(QString, int) = 0;
    virtual bool removeLibrary(QUuid) = 0;
    virtual bool updateLibrary(QUuid) = 0;

signals:
    void librariesChanged();
};

#endif // INTERFACESAVER_H

