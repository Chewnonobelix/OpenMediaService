#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QSharedPointer>
#include "global.h"

class PlayList;

typedef QSharedPointer<PlayList> PlayListPointer;

class PlayList
{
public:
    PlayList();
};

#endif // PLAYLIST_H
