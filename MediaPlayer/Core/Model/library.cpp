#include "library.h"

Library::Library(): QObject(nullptr)
{
    m_sourceDir<<"F:\\Musique\\Techno";

    connect(&m_probe, LibraryProbe::finished, this, Library::endProbe);
    connect(&m_probe, LibraryProbe::s_add, this, Library::addProbedMedia);
}

Library::~Library()
{}

void Library::addProbedMedia(MD5 md, QString path)
{
    if(m_medias.contains(md))
        (m_medias[md])<<path;
    else
    {
        auto n = Media::createMedia(md, path);
        m_medias[md] = n;
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
