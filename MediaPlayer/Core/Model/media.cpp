#include "media.h"

Media::Media(MD5 id, QString path)
{
    setId(id);
    m_path<<path;
}

MD5 Media::id() const
{
    return metaData<MD5>("id");
}

void Media::setId(MD5 id)
{
    setMetadata("id", id);
}

MediaPlayerGlobal::MediaRole Media::role() const
{
    return metaData<MediaPlayerGlobal::MediaRole>("role");
}

void Media::setRole(MediaPlayerGlobal::MediaRole role)
{
    setMetadata("role", role);
}

QString Media::path() const
{
    return *m_path.begin();
}

QSet<QString> Media::paths() const
{
    return m_path;
}

void Media::setPath(QString path)
{
    if(path.isEmpty())
        return;
 
    m_path<<path;
}

int Media::count() const
{
    return hasMetadata("count") ? metaData<int>("count") : 0;
}

void Media::setCount(int count)
{
    setMetadata("count", count);
}

QDate Media::added() const
{
    return metaData<QDate>("added");
}

void Media::setAdded(QDate added)
{
    setMetadata("added", added);
}

QDateTime Media::lastFinish() const
{
    return metaData<QDateTime>("lastFinish");
}

void Media::setLastFinish(QDateTime lastFinish)
{
    setMetadata("lastFinish", lastFinish);
}

double Media::currentRead() const
{
    return metaData<double>("currentRead");
}

void Media::setCurrentRead(double currentRead)
{
    setMetadata("currentRead", currentRead);
}

MediaPointer Media::createMedia(MD5 id, QString path)
{
    MediaPointer ret = MediaPlayerGlobal::factory<Media>(id, path);
    ret->setAdded(QDate::currentDate());
    ret->setRole(MediaPlayerGlobal::getRole(path));
    
    return ret;
}

MediaPointer operator << (MediaPointer p, QString path)
{
    p->setPath(path);
    return p;
}

void Media::operator ++ ()
{
    setCount(count() + 1);
}

int Media::nbPath() const
{
    return m_path.size();
}

bool Media::isAvailable() const
{
    return !m_path.isEmpty();
}

