#include "library.h"

Library::Library(): QObject(nullptr)
{
    m_sourceDir<<"C:\\Perso\\MediaPlayer\\build-MediaPlayer-Desktop_Qt_5_13_0_MinGW_64_bit-Debug\\hexagone\\\Musique save\\Variete\\Renaud";
    
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

    qDebug()<<m_medias.size()<<nPath;
}

void Library::probe()
{
    m_probe.baseName = m_sourceDir.toList();
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
