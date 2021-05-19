#include "controllerlibrary.h"

void ControllerLibrary::exec() {
    connect(&m_playlist, &PlaylistModel::currentIndexChanged, this,
                    &ControllerLibrary::onCurrentPlaylistChanged);
}

PlaylistModel *ControllerLibrary::playlist() { return &m_playlist; }

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

void ControllerLibrary::setCurrentLibrary(LibraryPointer lib) {
    m_current = lib;
    connect(m_current.data(), &Library::libraryChanged, this,
                    &ControllerLibrary::onUpdateLibrary, Qt::UniqueConnection);
//    m_plugin = m_manager[m_current->role()]->clone();
//    m_plugin->exec();

    emit libraryChanged();

//    m_current->probe()->setFilters(m_plugin->filters());
    m_playlist.setSmart(m_current->smartPlaylist().values());
    m_playlist.setNormal(m_current->playlist().values());
}

void ControllerLibrary::onUpdateLibrary() {
	db()->updateLibrary(m_current);
    m_playlist.setSmart(m_current->smartPlaylist().values());
    m_playlist.setNormal(m_current->playlist().values());
}

void ControllerLibrary::onCurrentPlaylistChanged(PlaylistPointer p) {
    if(p) {
        connect(p.data(), &PlayList::play, this, &ControllerLibrary::onPlay, Qt::UniqueConnection);
//        m_currentPlaylist = p;
    }

//    if (m_plugin && p) {
//		m_plugin->setPlaylist(p);
//	}
}

QString ControllerLibrary::id() const { return m_id.toString(); }

void ControllerLibrary::onPlay(MediaPointer m)
{
    emit play(m.data());
}

void ControllerLibrary::setPlaylistIndex(QString id, int index)
{
    if(index == -1)
        m_plugins.remove(QUuid::fromString(id));

    if(!m_plugins.contains(QUuid::fromString(id))) {
        m_plugins[QUuid::fromString(id)] = m_manager[m_current->role()]->clone();
         m_plugins[QUuid::fromString(id)]->exec();
    }

    if(index != -1)
        m_plugins[QUuid::fromString(id)]->setPlaylist(m_playlist[index]);
}

QQmlComponent* ControllerLibrary::playerComp(QString id)
{
    return m_plugins.contains(QUuid::fromString(id)) ? m_plugins[QUuid::fromString(id)]->playerView() : nullptr;
}

QQmlComponent* ControllerLibrary::playlistComp(QString id)
{
    return m_plugins.contains(QUuid::fromString(id)) ? m_plugins[QUuid::fromString(id)]->playlistView() : nullptr;
}

