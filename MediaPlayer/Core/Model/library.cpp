#include "library.h"

Library::Library(const Library&)
{}

Library& Library::operator = (const Library&)
{
    return *this;
}

void Library::probe() 
{}

QUuid Library::id() const 
{
    return QUuid();
}

void Library::setId(QUuid)
{}

QString Library::name() const
{
    return QString();
}

void Library::setName(QString)
{
    
}

MediaPlayerGlobal::MediaRole Library::role() const
{
    return MediaPlayerGlobal::MediaRole::Undefined;    
}

void Library::setRole(MediaPlayerGlobal::MediaRole)
{}

bool Library::isShared() const
{
    return false;
}

void Library::setShared(bool)
{}

QDateTime Library::lastProbed() const
{
    return QDateTime();    
}

void Library::setLastProbed(QDateTime)
{}

QSet<QString> Library::sourceDir() const
{
    return QSet<QString>();
}

bool Library::addSourceDir(QString)
{
    return false;
}

bool Library::removeSourceDir(QString)
{
    return false;
}
