#include "controllerlibrary.h"

ControllerLibrary::ControllerLibrary(QQmlEngine &engine)
{
    auto *context = engine.rootContext();
    context->setContextProperty("_libraries", this);
}

ControllerLibrary::ControllerLibrary(const ControllerLibrary &) : AbstractController() {}

void ControllerLibrary::exec()
{
}

Library *ControllerLibrary::currentLibrary() const
{
 return m_currentLibrary;
}

void ControllerLibrary::setCurrentLibrary(Library *l)
{
 m_currentLibrary = l;

 emit currentLibraryChanged();
}
