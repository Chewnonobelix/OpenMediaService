#include "playlist.h"

PlayList::PlayList(const PlayList & p): QObject(nullptr), MetaData(p), QList(p)
{}

PlayList& PlayList::operator= (const PlayList& p)
{
    MetaData& m = *this;
    m = p;
    QList<MediaPointer>& m2 = *this;
    m2 = p;
    
    return *this;
}

QUuid PlayList::id() const
{
    return metaData<QUuid>("id");
}

void PlayList::setId(QUuid id)
{
    setMetadata("id", id);
}

QString PlayList::name() const
{
    return metaData<QString>("name");
}

void PlayList::setName(QString name)
{
    setMetadata("name", name);
    emit nameChanged(name);
}

void PlayList::append(MediaPointer m, int index)
{
    if(index == -1)
        QList<MediaPointer>::append(m);
    else
        insert(index, m);
    
    emit countChanged();
}

void PlayList::remove(int index)
{
    removeAt(index);
    
    emit countChanged();
}

MediaPointer PlayList::at(int i) const
{
    return (*this)[i];
}

void PlayList::swap(int i, int j)
{
    swapItemsAt(i, j);
    
    emit countChanged();
}

void PlayList::clear()
{
    QList<MediaPointer>::clear();
    emit countChanged();
}
