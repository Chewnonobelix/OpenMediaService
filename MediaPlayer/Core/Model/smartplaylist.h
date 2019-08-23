#ifndef SMARTPLAYLIST_H
#define SMARTPLAYLIST_H

#include "playlist.h"

class SmartPlaylist: public PlayList
{
private:
    QVariantMap m_critera;
    
public:
    SmartPlaylist() = default;
    
    void update();
};

#endif // SMARTPLAYLIST_H
