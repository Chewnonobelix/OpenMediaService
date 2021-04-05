#include "controllerlibrary.h"

void ControllerLibrary::exec() {}

PlaylistModel *ControllerLibrary::playlist() const { return m_playlist; }

void ControllerLibrary::open() {
	auto context = m_engine->qmlEngine().rootContext();
	context->setContextProperty("_libraries", this);
	m_engine->createWindow(QUrl(QStringLiteral("/LibraryView.qml")));
}

void ControllerLibrary::addSourceDir(QString source) {
	m_current->addSourceDir(source);
}

void ControllerLibrary::removeSourceDir(QString path) {
	m_current->removeSourceDir(path);
}

void ControllerLibrary::addPlaylist(bool smart) {
	if (smart) {
		auto pl = factory<SmartPlaylist>();
		m_current->addSmartPlaylist(pl);
	} else {
		auto pl = factory<PlayList>();
		m_current->addPlaylist(pl);
	}
}

void ControllerLibrary::removePlaylist(QString id) {
	m_current->removePlaylist(id);
	m_current->removeSmartPlaylist(id);
}

Library *ControllerLibrary::library() const { return m_current.data(); }

void ControllerLibrary::setCurrentLibrary(QString id) {
	auto uid = QUuid::fromString(id);
	m_current = (*m_librariesModel)[uid];
    connect(m_current.data(), &Library::libraryChanged, this, &ControllerLibrary::onUpdateLibrary, Qt::UniqueConnection);
    auto plugin = m_manager[m_current->role()]->clone();
    m_current->probe()->setFilters(plugin->filters());
	emit libraryChanged();
    m_playlist->setSmart(m_current->smartPlaylist().values());
    m_playlist->setNormal(m_current->playlist().values());
}

void ControllerLibrary::onUpdateLibrary()
{
    db()->updateLibrary(m_current);
    m_playlist->setSmart(m_current->smartPlaylist().values());
    m_playlist->setNormal(m_current->playlist().values());
}
