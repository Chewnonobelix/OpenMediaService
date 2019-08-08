#include "interfacesaver.h"

InterfaceSaver::InterfaceSaver(): QObject(nullptr), m_role(MediaRole::Undefined)
{}

InterfaceSaver::InterfaceSaver(const InterfaceSaver& is): QObject(nullptr), m_role(is.role()), m_name(is.name())
{}

InterfaceSaver::~InterfaceSaver()
{}

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
