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

    emit libraryChanged();

    m_current->probe()->setFilters(s_manager[m_current->role()]->filters());
    m_playlist.setSmart(m_current->smartPlaylist().values());
    m_playlist.setNormal(m_current->playlist().values());
}

void ControllerLibrary::onUpdateLibrary() {
    db()->updateLibrary(m_current);
    m_playlist.onLibraryChanged(m_current);
}

void ControllerLibrary::onCurrentPlaylistChanged() {
    auto p = m_playlist.current();

    auto plugin = m_plugins[s_tabWrapper->currentId()];
    if (plugin && p) {

        s_tabWrapper->setPlaylist(p);
        plugin->setPlaylist(p);
    }
}

QString ControllerLibrary::id() const { return m_id.toString(); }

void ControllerLibrary::onPlay(MediaPointer m)
{
    auto src = (InterfacePlugins*)sender();

    emit play(src->id(), m.data());
}

void ControllerLibrary::setPlaylistIndex(QString id, int index)
{
    if(index == -1 && m_plugins.contains(QUuid::fromString(id)))
        m_plugins.remove(QUuid::fromString(id));

    if(!m_plugins.contains(QUuid::fromString(id)) || !m_plugins[QUuid::fromString(id)]) {
        m_plugins[QUuid::fromString(id)] = s_manager[m_current->role()]->clone();
         m_plugins[QUuid::fromString(id)]->exec();
    }

    if(index != -1 &&  m_plugins.contains(QUuid::fromString(id))) {
        m_plugins[QUuid::fromString(id)]->setPlaylist(m_playlist[index]);
        m_plugins[QUuid::fromString(id)]->setID(QUuid::fromString(id));

        s_tabWrapper->setPlaylist(m_playlist[index]);
    }
}

QQmlComponent* ControllerLibrary::playerComp(QString id)
{
    return m_plugins.contains(QUuid::fromString(id)) ? m_plugins[QUuid::fromString(id)]->playerView() : nullptr;
}

QQmlComponent* ControllerLibrary::playlistComp(QString id)
{
    auto uid = id.isEmpty() ? s_tabWrapper->currentId() : QUuid::fromString(id);
    return m_plugins.contains(uid) ? m_plugins[uid]->playlistView() : nullptr;
}

