#include "tabwrapper.h"

QUuid TabWrapper::create()
{
    auto manager = new TabManager;
    m_model[manager->id()] = manager;

    connect(manager, &TabManager::clicked, this, &TabWrapper::setCurrentTab);

    return manager->id();
}

QPointer<TabManager> TabWrapper::get(QUuid id)
{
    return m_model.contains(id) ? m_model[id] : nullptr;
}

QPointer<TabManager> TabWrapper::get(QString id)
{
    return get(QUuid::fromString(id));
}

void TabWrapper::setCurrentTab(QString id)
{
    m_current = QUuid::fromString(id);
}
