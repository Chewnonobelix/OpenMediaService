#include "playlist.h"

bool PlayList::basicPlaylist() const
{
    return m_basicPlaylist;
}

void PlayList::setBasicPlaylist(bool basicPlaylist)
{
    m_basicPlaylist = basicPlaylist;
}

bool PlayList::lock() const
{
    return m_lock;
}

void PlayList::setLock(bool lock)
{
    m_lock = lock;
}

PlayList::PlayList(): QObject(nullptr)
{
    setMetadata("id", QUuid::createUuid().toString());
}

PlayList::PlayList(const PlayList& other): QObject(nullptr), Metadata(other), m_playlist(other.playlist()),
    m_basicPlaylist(other.basicPlaylist()), m_lock(other.lock())
{
}

QString PlayList::name() const
{
    return metaData<QString>("name");    
}

void PlayList::setName(QString name)
{
    setMetadata("name", name);
}

QString PlayList::id() const
{
    return metaData<QString>("id");
}

void PlayList::addMedia(MediaPointer m)
{
    m_playlist<<m;    
}

void PlayList::removeMedia(int index)
{
    m_playlist.removeAt(index);    
}

void PlayList::removeMedia(MediaPointer m)
{
    m_playlist.removeAll(m);    
}

QList<MediaPointer> PlayList::playlist() const
{
    return m_playlist;
}
