#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QList>
#include <QSharedPointer>
#include <QVariant>
#include <QUuid>
#include "global.h"
#include "media.h"

class PlayList;

typedef QSharedPointer<PlayList> PlayListPointer;

class PlayList: public QObject,  public MetaData
{
    Q_OBJECT 
    
private:
    
public:
    PlayList() = default;
    PlayList(const PlayList &) = default;
    ~PlayList() = default;
};

#endif // PLAYLIST_H
