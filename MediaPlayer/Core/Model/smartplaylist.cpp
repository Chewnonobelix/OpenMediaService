#include "smartplaylist.h"

void SmartPlaylist::update()
{
   
}

void SmartPlaylist::setCritera(QString name, QVariant value)
{
    m_critera[name] = value;
}

void SmartPlaylist::removeCritera(QString name)
{
    if(m_critera.contains(name))
         return m_critera.remove(name) > 0;
    
    return false;
}

QVariantMap SmartPlaylist::critera() const
{
    return m_critera;
}
