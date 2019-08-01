#ifndef LIBRARY_H
#define LIBRARY_H

#include <QMap>
#include "media.h"
#include "playlist.h"

class Library
{
private:
    QString m_name;
    MediaPlayerGlobal::MediaRole m_role;    
    QMap<MD5, MediaPointer> m_medias;    
    QList<PlayListPointer> m_playlists;
    
public:
    Library();
};

#endif // LIBRARY_H
