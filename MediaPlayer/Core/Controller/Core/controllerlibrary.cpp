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
	emit libraryChanged();
}
