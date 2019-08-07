#ifndef INTERFACESAVER_H
#define INTERFACESAVER_H


#include "Model/global.h"
#include "Model/media.h"

using namespace MediaPlayerGlobal;

class InterfaceSaver
{
private:
    MediaRole m_role;
    QString m_name;
    
public:
    MediaRole role() const;
    void setRole(MediaRole role);
    QString name() const;
    void setName(QString name);
    
    virtual void init() = 0;
    
    virtual QMap<MD5, MediaPointer> selectMedia() = 0;
    virtual bool addMedia(MediaPointer) = 0;
    virtual bool removeMedia(MediaPointer) = 0;
    virtual bool updateMedia(MediaPointer) = 0;
    
    
};

#endif // INTERFACESAVER_H

