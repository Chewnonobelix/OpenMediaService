#include "media.h"

Media::Media(MD5 id, QString path)
{
    setId(id);
    m_path<<path;
}

MD5 Media::id() const
{
    return m_metadata["id"].toByteArray();
}

void Media::setId(MD5 id)
{
    m_metadata["id"] = id;
}

MediaPlayerGlobal::MediaRole Media::role() const
{
    return m_metadata["role"].value<MediaPlayerGlobal::MediaRole>();
}

void Media::setRole(MediaPlayerGlobal::MediaRole role)
{
    m_metadata["role"] = role;
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
    return hasMetadata("count") ? m_metadata["count"].toInt() : 0;
}

void Media::setCount(int count)
{
    m_metadata["count"] = count;
}

QDate Media::added() const
{
    return m_metadata["added"].toDate();
}

void Media::setAdded(QDate added)
{
    m_metadata["added"] = added;
}

QDateTime Media::lastFinish() const
{
    return m_metadata["lastFinish"].toDateTime();
}

void Media::setLastFinish(QDateTime lastFinish)
{
    m_metadata["lastFinish"] = lastFinish;
}

double Media::currentRead() const
{
    return m_metadata["currentRead"].toDouble();
}

void Media::setCurrentRead(double currentRead)
{
    m_metadata["currentRead"] = currentRead;
}

MediaPointer Media::createMedia(MD5 id, QString path)
{
    MediaPointer ret = MediaPlayerGlobal::factory<Media>(id, path);
//    ret->setPath(path);
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

QStringList Media::metaDataList() const
{
    return m_metadata.keys();
}

bool Media::hasMetadata(QString key) const
{
    return m_metadata.contains(key);
}

bool Media::hasMetadata() const
{
    return !m_metadata.empty();
}



