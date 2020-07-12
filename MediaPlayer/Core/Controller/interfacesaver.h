#ifndef INTERFACESAVER_H
#define INTERFACESAVER_H

#include <QObject>

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
    
};

#endif // INTERFACESAVER_H

