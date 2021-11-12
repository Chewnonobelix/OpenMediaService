#include "controllerlibrary.h"

Q_LOGGING_CATEGORY(librarylog, "library.log")

void ControllerLibrary::exec() {
    connect(&m_playlist, &PlaylistModel::currentIndexChanged, this,
                    &ControllerLibrary::onCurrentPlaylistChanged);
}

PlaylistModel *ControllerLibrary::playlist() { return &m_playlist; }

void ControllerLibrary::open() {
    auto context = new QQmlContext(engine()->qmlEngine().rootContext());
    context->setContextProperty("_libraries", this);
    qCDebug(librarylog) << "Library context";
    engine()->createWindow(QUrl(QStringLiteral("/LibraryView.qml")), context);
}

void ControllerLibrary::addSourceDir(QString source) {
    m_current->addSourceDir(source);
}

void ControllerLibrary::removeSourceDir(QString path) {
    m_current->removeSourceDir(path);
}

QUuid ControllerLibrary::addPlaylist(bool smart) {
    QUuid ret;
    if (smart) {
        auto pl = factory<SmartPlaylist>();
        m_current->addSmartPlaylist(pl);
        ret = pl->id();
    } else {
        auto pl = factory<PlayList>();
        m_current->addPlaylist(pl);
        ret = pl->id();
    }
    m_playlist.onLibraryChanged(m_current);

    return ret;
}

void ControllerLibrary::removePlaylist(QString id) {
    m_current->removePlaylist(id);
    m_current->removeSmartPlaylist(id);
    m_playlist.onLibraryChanged(m_current);
}

Library *ControllerLibrary::library() const { return m_current.data(); }

void ControllerLibrary::setCurrentLibrary(LibraryPointer lib) {
    if(lib.isNull())
        return;

    m_current = lib;
    connect(m_current.data(), &Library::libraryChanged, this,
                    &ControllerLibrary::onUpdateLibrary, Qt::UniqueConnection);

    emit libraryChanged();

    m_current->probe()->setFilters(s_manager[m_current->role()]->filters());
    m_playlist.onLibraryChanged(m_current);
}

void ControllerLibrary::onUpdateLibrary() {
    db()->updateLibrary(m_current);
}

void ControllerLibrary::onCurrentPlaylistChanged() {
    auto p = m_playlist.current();

    auto plugin = m_plugins[s_tabWrapper->currentId()];
    if (plugin && p) {

        s_tabWrapper->setPlaylist(m_playlist.currentIndex());
        plugin->setPlaylist(p);
    }
}

QString ControllerLibrary::id() const { return m_id.toString(); }

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

        s_tabWrapper->setPlaylist(index);
    }
}

QObject* ControllerLibrary::playerComp(QString id)
{
    return m_plugins.contains(QUuid::fromString(id)) ? m_plugins[QUuid::fromString(id)]->playerView() : nullptr;
}

QObject* ControllerLibrary::playlistComp(QString id)
{
    auto uid = id.isEmpty() ? s_tabWrapper->currentId() : QUuid::fromString(id);
    return m_plugins.contains(uid) ? m_plugins[uid]->playlistView() : nullptr;
}

bool ControllerLibrary::containView(QUuid id) const
{
    return m_plugins.keys().contains(id);
}

void ControllerLibrary::setModelIndex(int index)
{
    m_playlist.setCurrentIndex(index);
}

QList<QVariantMap> ControllerLibrary::importers() const
{
    QList<QVariantMap> ret;
    if(!m_plugins.isEmpty()) {
        for(auto it: m_plugins.first()->importers()) {
            QVariantMap map;
            map["name"] = it->name();
            map["filters"] = it->filters();
            ret<<map;
        }
    }

    return ret;
}

void ControllerLibrary::importFrom(QString importer, QString file)
{
    qDebug()<<importer<<file<<m_plugins.count();

    if(m_plugins.count() == 0)
        return;

    auto imp = *(std::find_if(m_plugins.first()->importers().begin(), m_plugins.first()->importers().end(), [importer](auto it) {
       return it->name() == importer;
    }));

    connect(imp.data(), &InterfaceImporter::findMedia, [this](auto m) {
        m_current->addMedia(m);
    });

    connect(imp.data(), &InterfaceImporter::findWatchfolder, [this](auto w) {
        m_current->addSourceDir(w);
    });

    connect(imp.data(), &InterfaceImporter::findPlaylist, [this](PlaylistPointer p) {
        if(p.dynamicCast<SmartPlaylist>()) {
            m_current->addSmartPlaylist(p.dynamicCast<SmartPlaylist>());
        }
        else{
            m_current->addPlaylist(p);
        }

    });

    imp->import(file.remove(0, 8));
}
