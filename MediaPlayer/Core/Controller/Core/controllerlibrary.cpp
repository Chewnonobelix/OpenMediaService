#include "controllerlibrary.h"

ControllerLibrary::ControllerLibrary()
{
    auto *context = m_engine->qmlEngine().rootContext();
    context->setContextProperty("_libraries", this);
    context->setContextProperty("_librariesModel", &m_librariesModel);

    connect(&m_librariesModel, &LibraryDataModel::currentModelChanged, this, &ControllerLibrary::onCurrentModelChanged);
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
    auto lib =  db()->selectLibrary()[QUuid::fromString(l)];

    m_currentLibrary = lib;

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

void ControllerLibrary::removeSourceDir(QString path)
{
    m_currentLibrary->removeSourceDir(path);
    db()->updateLibrary(m_currentLibrary);
}

void ControllerLibrary::onCurrentModelChanged(LibraryPointer p)
{
    m_currentLibrary = p;
    emit currentLibraryChanged();
}

