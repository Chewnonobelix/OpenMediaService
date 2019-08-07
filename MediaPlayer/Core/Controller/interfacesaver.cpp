#include "interfacesaver.h"

QString InterfaceSaver::name() const
{
    return m_name;
}

void InterfaceSaver::setName(QString name)
{
    m_name = name;
}

MediaRole InterfaceSaver::role() const
{
    return m_role;
}

void InterfaceSaver::setRole(MediaRole role)
{
    m_role = role;
}
