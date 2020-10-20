#include "controllerlibrary.h"

ControllerLibrary::ControllerLibrary()
{
    auto *context = m_engine->qmlEngine().rootContext();
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

void ControllerLibrary::open()
{
    m_engine->createWindow(QUrl(QStringLiteral("/LibraryView.qml")));
}
