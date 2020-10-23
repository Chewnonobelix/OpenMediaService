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
 return m_currentLibrary.data();
}

void ControllerLibrary::setCurrentLibrary(QString l)
{
 m_currentLibrary = db()->selectLibrary()[QUuid::fromString(l)];

 emit currentLibraryChanged();
}

void ControllerLibrary::open()
{
    m_engine->createWindow(QUrl(QStringLiteral("/LibraryView.qml")));
}

void ControllerLibrary::addSourceDir(QString source)
{
 m_currentLibrary->addSourceDir(source);
 db()->updateLibrary(m_currentLibrary);
}
