#include "media.h"

Media::Media(MD5 id, QString path): m_role(MediaPlayerGlobal::Undefined), m_count(0), m_currentRead(0)
{
    m_id = id;
    m_path<<path;
}

MD5 Media::id() const
{
    return m_id;
}

void Media::setId(MD5 id)
{
    m_id = id;
}

MediaPlayerGlobal::MediaRole Media::role() const
{
    return m_role;
}

void Media::setRole(MediaPlayerGlobal::MediaRole role)
{
    m_role = role;
}

QString Media::path() const
{
    return *m_path.begin();
}

void Media::setPath(QString path)
{
    m_path<<path;
}

int Media::count() const
{
    return m_count;
}

void Media::setCount(int count)
{
    m_count = count;
}

QDate Media::added() const
{
    return m_added;
}

void Media::setAdded(QDate added)
{
    m_added = added;
}

QDateTime Media::lastFinish() const
{
    return m_lastFinish;
}

void Media::setLastFinish(QDateTime lastFinish)
{
    m_lastFinish = lastFinish;
}

double Media::currentRead() const
{
    return m_currentRead;
}

void Media::setCurrentRead(double currentRead)
{
    m_currentRead = currentRead;
}

MediaPointer Media::createMedia(MD5 id, QString path)
{
    MediaPointer ret = MediaPointer::create(id, path);
    ret->setPath(path);
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
   m_count ++;
}

int Media::nbPath() const
{
    return m_path.size();
}

bool Media::isAvailable() const
{
    return !m_path.isEmpty();
}
