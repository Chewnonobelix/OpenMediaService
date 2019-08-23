#include "playlist.h"

PlayList::PlayList()
{
    setMetadata("id", QUuid::createUuid().toString());
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
