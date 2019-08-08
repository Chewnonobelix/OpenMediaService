#include "controllerlibrary.h"

ControllerLibrary::ControllerLibrary(): QObject(nullptr)
{
    
}

ControllerLibrary::~ControllerLibrary()
{}

bool ControllerLibrary::addLibrary(QString name, MediaRole role)
{
    bool ret = false;
    
    
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
