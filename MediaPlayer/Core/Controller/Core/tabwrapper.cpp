#include "tabwrapper.h"

QUuid TabWrapper::create()
{
    auto manager = new TabManager;
    m_model[manager->id()] = manager;

    connect(manager, &TabManager::clicked, [this](QUuid id) {
        m_current = id;
    });

    return manager->id();
}

QPointer<TabManager> TabWrapper::get(QUuid id)
{
    return m_model.contains(id) ? m_model[id] : nullptr;
}
