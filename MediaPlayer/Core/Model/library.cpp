#include "library.h"

Library::Library(const Library& l): MetaData(l)
{}

Library& Library::operator = (const Library& l)
{
    MetaData& mt = *this;
    mt = l;
    return *this;
}

void Library::probe() 
{}

QUuid Library::id() const 
{
    return metaData<QUuid>("id");
}

void Library::setId(QUuid id)
{
    setMetadata("id", id);    
}

QString Library::name() const
{
    return metaData<QString>("name");
}

void Library::setName(QString name)
{
    setMetadata("name", name);  
    emit nameChanged(name);
}

MediaPlayerGlobal::MediaRole Library::role() const
{
    return metaData<MediaPlayerGlobal::MediaRole>("role");    
}

void Library::setRole(MediaPlayerGlobal::MediaRole role)
{
    setMetadata("role", role);
}

bool Library::isShared() const
{
    return metaData<bool>("shared");
}

void Library::setShared(bool shared)
{
    setMetadata("shared", shared);
    emit isSharedChanged(shared);
}

QDateTime Library::lastProbed() const
{
    return metaData<QDateTime>("lastProbed");    
}

void Library::setLastProbed(QDateTime lp)
{
    setMetadata("lastProbed", lp);
    emit lastProbedChanged(lp);
}

QSet<QString> Library::sourceDir() const
{
    return metaData<QSet<QString>>("sourceDir");
}

bool Library::addSourceDir(QString source)
{
    auto t = sourceDir();
    bool ret = t.contains(source);
    t<<source;
    setMetadata("sourceDir", t);
    emit sourceDirChanged(t);
    return !ret;;
}

bool Library::removeSourceDir(QString source)
{
    auto t = sourceDir();
    bool ret = t.remove(source);
    setMetadata("sourceDir", t);    
    emit sourceDirChanged(t);
    return ret;;
}

bool Library::addMedia(QString path)
{
    return false;        
}

bool Library::removeMedia(QString path)
{
    return false;
}

QMap<MD5, MediaPointer> Library::medias(MD5 id) const
{
    return QMap<MD5, MediaPointer>();
}
