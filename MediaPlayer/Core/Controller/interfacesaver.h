#ifndef INTERFACESAVER_H
#define INTERFACESAVER_H


#include "global.h"
#include "media.h"

using namespace MediaPlayerGlobal;

class InterfaceSaver
{
public:
    virtual QMap<MD5, Media> selectMedia(MediaRole = Undefined) = 0;
    virtual bool addMedia(MediaPointer) = 0;
    virtual bool removeMedia(MediaPointer) = 0;
    virtual bool updateMedia(MediaPointer) = 0;
};

#endif // INTERFACESAVER_H
