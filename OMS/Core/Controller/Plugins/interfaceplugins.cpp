#include "interfaceplugins.h"

QUuid InterfacePlugins::id() const
{
    return m_tabId;
}

void InterfacePlugins::setID(QUuid id)
{
    m_tabId = id;
}
