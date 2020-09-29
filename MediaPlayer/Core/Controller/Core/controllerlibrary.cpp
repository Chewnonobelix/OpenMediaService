#include "controllerlibrary.h"

ControllerLibrary::ControllerLibrary(QQmlEngine &engine)
{
    auto *context = engine.rootContext();
    context->setContextProperty("_libraryModel", &m_ldm);
    context->setContextProperty("_libraries", this);
}

ControllerLibrary::ControllerLibrary(const ControllerLibrary &) : AbstractController() {}

void ControllerLibrary::onLibrariesChanged()
{
    m_ldm.clear();

    for (auto it : db()->selectLibrary())
        m_ldm.insertData(it);
}

void ControllerLibrary::exec()
{
    for (auto it : db()->selectLibrary())
        m_ldm.insertData(it);

    m_ldm.sort(0, Qt::DescendingOrder);

    connect(db(),
            &InterfaceSaver::librariesChanged,
            this,
            &ControllerLibrary::onLibrariesChanged,
            Qt::UniqueConnection);
}
