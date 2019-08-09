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
    qDebug()<<name;
    auto lib = factory<Library>();
    
    int type = QMetaType::type("XmlDatabase");
    if(type == QMetaType::UnknownType)
        throw QString("Unknow DB Type");
    
    InterfaceSaver* saver = (InterfaceSaver*)(QMetaType::create(type));
    QSharedPointer<InterfaceSaver> pis;
    pis.reset(saver);

    pis->setName(name);
    pis->init();

    m_libs<<qMakePair(lib, pis);

    connect(lib.data(), Library::s_addMedia, pis.data(), InterfaceSaver::addMedia);
    connect(lib.data(), Library::s_updateMedia, pis.data(), InterfaceSaver::updateMedia);
    connect(lib.data(), Library::s_removeMedia, pis.data(), InterfaceSaver::removeMedia);
    
    lib->setName(name);
    lib->setRole(pis->role());
    lib->setMedias(pis->selectMedia());    
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
    l->setRole(role);
    pis->init();
    
    connect(l.data(), Library::s_addMedia, pis.data(), InterfaceSaver::addMedia);
    connect(l.data(), Library::s_updateMedia, pis.data(), InterfaceSaver::updateMedia);
    connect(l.data(), Library::s_removeMedia, pis.data(), InterfaceSaver::removeMedia);
    
    m_libs.push_back(qMakePair(l, pis));
    
    qDebug()<<l->name()<<l->role()<<m_libs.size();
    return ret;
}

void ControllerLibrary::probeAll()
{
    for(auto it: m_libs)
        it.first->probe();
}
