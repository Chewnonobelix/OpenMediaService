#ifndef SMARTPLAYLIST_H
#define SMARTPLAYLIST_H

#include "playlist.h"

class SmartPlaylist: public PlayList
{
    Q_OBJECT
    
private:
    
public:
    SmartPlaylist() = default;
    SmartPlaylist(const SmartPlaylist&) = default;
    ~SmartPlaylist() = default;
   
public slots:
};

#endif // SMARTPLAYLIST_H
