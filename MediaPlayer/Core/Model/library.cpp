#include "library.h"

QMap<MD5, MediaPointer> Library::medias() const
{
    return m_medias;
}

void Library::setMedias(const QMap<MD5, MediaPointer> &medias)
{
    m_medias = medias;
}

QDateTime Library::lastProbed() const
{
    return m_lastProbed;
}

void Library::setLastProbed(QDateTime lastProbed)
{
    m_lastProbed = lastProbed;
    emit s_updateLastProbed(lastProbed);
}

Library::Library(): QObject(nullptr)
{
    
    connect(&m_probe, LibraryProbe::finished, this, Library::endProbe);
    connect(&m_probe, LibraryProbe::s_add, this, Library::addProbedMedia);
}

Library::~Library()
{}

void Library::addProbedMedia(MD5 md, QString path)
{
    if(m_medias.contains(md))
    {        
        (m_medias[md])<<path;
        emit s_updateMedia(m_medias[md]);
    }
    else
    {
        auto n = Media::createMedia(md, path);
        m_medias[md] = n;
        emit s_addMedia(n);
    }
}

void Library::endProbe()
{
    int nPath = 0;
    qDebug()<<"Endprobe;";
    for(auto it: m_medias)
        nPath += it->nbPath();
    setLastProbed(QDateTime::currentDateTime());
    qDebug()<<m_medias.size()<<nPath;
//    probe();
}

void Library::probe()
{
    m_probe.baseName = m_sourceDir.toList();
    m_probe.setLastProbed(lastProbed());
    m_probe.start();
}

QString Library::name() const
{
    return m_name;
}

void Library::setName(QString name)
{
    m_name = name;
}

MediaPlayerGlobal::MediaRole Library::role() const
{
    return m_role;
}

void Library::setRole(MediaPlayerGlobal::MediaRole role)
{
    m_role = role;
}

void Library::addSourceDir(QString srcDir)
{
    m_sourceDir<<srcDir;
    
    emit s_updateSourceDir(m_sourceDir);
}

QSet<QString> Library::sourceDir() const
{
    return m_sourceDir;
}

void Library::removeSourceDir(QString srcDir)
{
    m_sourceDir.remove(srcDir);
}

void Library::removeMedia(MD5 id)
{
    emit s_removeMedia(m_medias[id]);
    
    m_medias.remove(id);
}
