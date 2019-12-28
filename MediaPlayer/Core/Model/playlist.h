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
    QList<MediaPointer> m_playlist;
    bool m_basicPlaylist;
    bool m_lock;
    
public:
    PlayList();
    PlayList(const PlayList &);
    ~PlayList() = default;
    
    QString name() const;
    void setName(QString);
    
    QString id() const;
    
    void addMedia(MediaPointer);
    void removeMedia(int);
    void removeMedia(MediaPointer);
    QList<MediaPointer> playlist() const;
    
    bool basicPlaylist() const;
    void setBasicPlaylist(bool basicPlaylist);
    bool lock() const;
    void setLock(bool lock);
};

#endif // PLAYLIST_H
