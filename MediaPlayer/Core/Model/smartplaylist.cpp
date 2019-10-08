#include "smartplaylist.h"

void SmartPlaylist::update()
{
    QList<MediaPointer> toRemove;
    for(auto it: playlist())
        for(auto it2 = m_critera.begin(); it2 != m_critera.end(); it2++)
            if(!(it->hasMetadata(it2.key()) /*&& (it->metaData(it2.key()) == it2.value()))*/))
                    toRemove<<it;
    
    for(auto it: toRemove)
        removeMedia(it);
}
