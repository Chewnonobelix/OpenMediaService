#ifndef INTERFACESAVER_H
#define INTERFACESAVER_H

#include <QObject>

#include "Model/global.h"
#include "Model/media.h"

using namespace MediaPlayerGlobal;

class InterfaceSaver: public QObject
{
    
   Q_OBJECT
    
private:
    MediaRole m_role;
    QString m_name;
    
public:
    InterfaceSaver();
    InterfaceSaver(const InterfaceSaver&);
    virtual ~InterfaceSaver();
    
    MediaRole role() const;
    void setRole(MediaRole role);
    QString name() const;
    void setName(QString name);
    
    virtual void init() = 0;

public slots:    
    virtual QMap<MD5, MediaPointer> selectMedia() = 0;
    virtual bool addMedia(MediaPointer) = 0;
    virtual bool removeMedia(MediaPointer) = 0;
    virtual bool updateMedia(MediaPointer) = 0;
    
    virtual QSet<QString> selectSourceDir() = 0;
    virtual bool updateSourceDir(QSet<QString>) = 0;
   
    virtual QDateTime selectLastProbed() = 0;
    virtual bool updateLastProbed(QDateTime) = 0;
    
};

#endif // INTERFACESAVER_H

