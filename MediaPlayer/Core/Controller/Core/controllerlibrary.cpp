#include "controllerlibrary.h"

void ControllerLibrary::exec() {
	connect(m_playlist, &PlaylistModel::currentIndexChanged, this,
					&ControllerLibrary::onCurrentPlaylistChanged);
}

PlaylistModel *ControllerLibrary::playlist() const { return m_playlist; }

void ControllerLibrary::open() {
	auto context = m_engine->qmlEngine().rootContext();
	context->setContextProperty("_libraries", this);
	qDebug() << "Library context";
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
	connect(m_current.data(), &Library::libraryChanged, this,
					&ControllerLibrary::onUpdateLibrary, Qt::UniqueConnection);
	m_plugin = m_manager[m_current->role()]->clone();
	m_plugin->exec();

	emit libraryChanged();
	emit playerComponentChanged();
	emit playlistComponentChanged();

	m_current->probe()->setFilters(m_plugin->filters());
	m_playlist->setSmart(m_current->smartPlaylist().values());
	m_playlist->setNormal(m_current->playlist().values());
}

void ControllerLibrary::onUpdateLibrary() {
	db()->updateLibrary(m_current);
	m_playlist->setSmart(m_current->smartPlaylist().values());
	m_playlist->setNormal(m_current->playlist().values());
}

void ControllerLibrary::onCurrentPlaylistChanged(PlaylistPointer p) {
    disconnect(m_currentPlaylist.data(), &PlayList::play, this, &ControllerLibrary::onPlay);
    if(p) {
        connect(p.data(), &PlayList::play, this, &ControllerLibrary::onPlay);
        m_currentPlaylist = p;
    }

	if (m_plugin) {
		m_plugin->setPlaylist(p);
	}
}

QQmlComponent *ControllerLibrary::playlistComponent() const {
	return m_plugin ? m_plugin->playlistView() : nullptr;
}

QQmlComponent *ControllerLibrary::playerComponent() const {
	return m_plugin ? m_plugin->playerView() : nullptr;
}

QString ControllerLibrary::id() const { return m_id.toString(); }

int ControllerLibrary::currentIndex() const
{
    return m_currentIndex;
}

void ControllerLibrary::setCurrentIndex(int index)
{
    m_currentIndex = index;
    emit currentIndexChanged();
}

void ControllerLibrary::onPlay(MediaPointer m)
{
    emit play(m.data());
}
