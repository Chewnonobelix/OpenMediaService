#include "controllerlibrary.h"

ControllerLibrary::ControllerLibrary(): QObject(nullptr)
{
    QDir dir;
    if(!dir.cd("Library"))
    {
        dir.mkdir("Library");
        dir.cd("Library");
    }
    
    auto list = dir.entryInfoList(QStringList("*.xml"));
    
    for(auto it: list)
        open(it.absoluteFilePath());
    
}

ControllerLibrary::~ControllerLibrary()
{}

void ControllerLibrary::open(QString filename)
{
    qDebug()<<"Open "<<filename;
    auto name = filename.split("/").last().remove(".xml");

    addLibrary(name, MediaRole::Undefined);    
}

bool ControllerLibrary::addLibrary(QString name, MediaRole role)
{
    bool ret = false;
    
    for(auto it: m_libs)
        if(it.first->name() == name)
            return ret;
    
    int type = QMetaType::type("XmlDatabase");
    if(type == QMetaType::UnknownType)
        throw QString("Unknow DB Type");
    
    InterfaceSaver* saver = (InterfaceSaver*)(QMetaType::create(type));
    QSharedPointer<InterfaceSaver> pis;
    pis.reset(saver);
    auto l = factory<Library>();
    saver->setName(name);
    l->setName(name);
    saver->setRole(role);

    pis->init();
    l->setRole(pis->role());
    l->setMedias(pis->selectMedia());
    l->setLastProbed(pis->selectLastProbed());

    for(auto it: pis->selectSourceDir())
        l->addSourceDir(it);
    
    connect(l.data(), Library::s_addMedia, pis.data(), InterfaceSaver::addMedia);
    connect(l.data(), Library::s_updateMedia, pis.data(), InterfaceSaver::updateMedia);
    connect(l.data(), Library::s_removeMedia, pis.data(), InterfaceSaver::removeMedia);
    
    connect(l.data(), Library::s_updateLastProbed, pis.data(), InterfaceSaver::updateLastProbed);
    connect(l.data(), Library::s_updateSourceDir, pis.data(), InterfaceSaver::updateSourceDir);
    m_libs[l->name()] = qMakePair(l, pis);
    
    l->addSourceDir("C:\\Perso\\MediaPlayer\\build-MediaPlayer-Desktop_Qt_5_13_0_MinGW_64_bit-Debug\\hexagone\\");

    return ret;
}

void ControllerLibrary::probeAll()
{
    for(auto it: m_libs)
        it.first->probe();
}

QStringList ControllerLibrary::librariesName() const
{
    return m_libs.keys();
}

QPair<LibraryPointer, QSharedPointer<InterfaceSaver>> ControllerLibrary::library(QString name)
{
    return m_libs[name];
}
