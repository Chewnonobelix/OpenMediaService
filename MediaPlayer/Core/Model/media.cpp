#include "media.h"

Media::Media(MD5 id, QString path): QObject(nullptr)
{
    setId(id);
    if(!path.isEmpty())
        m_path<<path;
}


Media::Media(const Media &other): QObject(nullptr), MetaData(other), m_path(other.paths().begin(), other.paths().end())
{

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

QList<QString> Media::paths() const
{
    return m_path.values();
}

void Media::setPath(QString path)
{
    if(path.isEmpty())
        return;
 
    m_path<<path;
    emit isAvailableChanged(!m_path.isEmpty());
}

void Media::removePath(QString path)
{
    m_path.remove(path);   
    emit isAvailableChanged(!m_path.isEmpty());
}

int Media::count() const
{
    return hasMetadata("count") ? metaData<int>("count") : 0;
}

void Media::setCount(int count)
{
    setMetadata("count", count);
    emit countChanged(count);
}

int Media::rating() const
{
    return hasMetadata("rating") ? metaData<int>("rating") : 0;
}

void Media::setRating(int rate)
{
    setMetadata("rating", rate);
    emit ratingChanged(rate);
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
    emit lastFinishChanged(lastFinish);
}

QDateTime Media::lastProbed() const
{
    return metaData<QDateTime>("lastProbed");
}

void Media::setLastProbed(QDateTime lastProbed)
{
    setMetadata("lastProbed", lastProbed);
    emit lastProbedChanged(lastProbed);
}

double Media::currentRead() const
{
    return metaData<double>("currentRead");
}

void Media::setCurrentRead(double currentRead)
{
    setMetadata("currentRead", currentRead);
    emit currentReadChanged(currentRead);
}

MediaPointer Media::createMedia(MD5 id, QString path)
{
    MediaPointer ret = factory<Media>(id, path);
    ret->setAdded(QDate::currentDate());
    ret->setRole(MediaPlayerGlobal::getRole(path));
    
    return ret;
}

int Media::nbPath() const
{
    return m_path.size();
}

bool Media::isAvailable() const
{
    bool ret = !m_path.isEmpty();
    for(auto it = m_path.begin(); ret && it != m_path.end(); it++)
        ret &= QFile::exists(*it);
    
    return ret;
}

Media& Media::operator =(const Media& other)
{

    m_path.clear();
    for(auto it: other.paths())
        m_path<<it;

    MetaData& mt = *this;
    mt = other;
    return *this;
}
