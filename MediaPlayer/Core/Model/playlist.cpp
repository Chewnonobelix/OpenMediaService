#include "playlist.h"

PlayList::PlayList(const PlayList &): QObject(nullptr), MetaData(), QList()
{}

PlayList& PlayList::operator= (const PlayList&)
{
    return *this;
}

QUuid PlayList::id() const
{
    return QUuid();
}

void PlayList::setId(QUuid)
{}

QString PlayList::name() const
{
    return QString();
}

void PlayList::setName(QString)
{}

void PlayList::append(MediaPointer, int)
{}

void PlayList::remove(int)
{}

MediaPointer PlayList::at(int i) const
{
    return MediaPointer();
}

void PlayList::swap(int, int)
{}

void PlayList::clear()
{}
