#include "library.h"

Library::Library() { set(); }

Library::Library(const Library &l) : QObject(nullptr), MetaData(l), QEnableSharedFromThis<Library>() { set(); }

Library::Library(QJsonObject &l) : QObject(nullptr), MetaData(l)
{
    set();

    auto dirs = l["sourceDir"].toArray();
    auto ms = l["medias"].toArray();
    auto smarts = l["smartPlaylist"].toArray();
    auto plays = l["playlist"].toArray();
    auto tag = l["tags"].toArray();

    for (auto it : dirs)
        addSourceDir(it.toString());

    for (auto it : smarts) {
        auto s = factory<SmartPlaylist>(it.toObject());
        addSmartPlaylist(s);
    }

    for (auto it : plays) {
        auto s = factory<PlayList>(it.toObject());
        addPlaylist(s);
    }

    for (auto it : ms) {
        auto m = factory<Media>(it.toObject());
        addMedia(m);
    }

    for (auto it: tag) {
        auto obj = it.toObject();
        MediaPlayerGlobal::Tag t;
        t.first = QUuid::fromString(obj["id"].toString());
        t.second = obj["tag"].toString();
        addTag(t);
    }

    if(m_replacer)
        m_replacer->start();

    m_probe.setLastProbed(
                QDateTime::fromString(l["lastProbe"].toString(), "dd-MM-yyyy hh:mm:ss"));

}

void Library::set() {
    connect(this, &Library::nameChanged, this, &Library::libraryChanged);
    connect(this, &Library::isSharedChanged, this, &Library::libraryChanged);
    connect(this, &Library::sourceDirChanged, this, &Library::libraryChanged);
    connect(this, &Library::lastUpdateChanged, this, &Library::libraryChanged);
    connect(this, &Library::playlistCountChanged, this, &Library::libraryChanged);

    connect(&m_probe, &LibraryProbe::mediaFind, this, &Library::addMedia,
            Qt::QueuedConnection);
    connect(&m_probe, &LibraryProbe::currentChanged, this,
            &Library::onProbedChanged);

    m_replacer = QThread::create([this]() {
        auto list = m_playlist.values();
        for(auto it: m_smartPlaylist)
            list<<it;

        for(auto it: m_medias) {
            for(auto it2: list) {
                it2->replace(it);
            }
        }
    });

}

Library::operator QJsonObject() const {
    auto ret = MetaData::operator QJsonObject();

    QJsonArray ms, sources, smarts, plays;

    auto appender = [](auto container, auto &list) {
        for (auto it : container) {
            list << QJsonObject(*it);
        }
    };

    for (auto it : sourceDir())
        sources << it;

    appender(m_medias, ms);
    appender(m_smartPlaylist, smarts);
    appender(m_playlist, plays);

    ret["medias"] = ms;
    ret["sourceDir"] = sources;
    ret["smartPlaylist"] = smarts;
    ret["playlist"] = plays;
    ret["lastProbe"] = m_probe.lastProbed().toString("dd-MM-yyyy hh:mm:ss");

    auto tl = tags();
    QJsonArray vl;
    for(auto it: tl) {
        QJsonObject obj;
        obj["id"] = it.first.toString();
        obj["tag"] = it.second;
        vl<<obj;
    }

    ret["tags"] = vl;

    return ret;
}

Library &Library::operator=(const Library &l) {
    MetaData &mt = *this;
    mt = l;
    return *this;
}

bool Library::scan() {
    //TODO
    QSet<QString> paths;
    for (auto it : m_medias)
        for (auto it2 : it->paths())
            paths << it2;

    m_probe.setPaths(paths);
    m_probe.setSourceDir(sourceDir());
    m_probe.setRole(role());
    m_probe.probe();

    return true;
}

QUuid Library::id() const { return metaData<QUuid>("id"); }

bool Library::setId(QUuid id) { return setMetadata("id", id); }

QString Library::name() const { return metaData<QString>("name"); }

bool Library::setName(QString name) {
    auto ret = setMetadata("name", name);
    emit nameChanged();
    return ret;
}

MediaPlayerGlobal::MediaRole Library::role() const {
    return metaData<MediaPlayerGlobal::MediaRole>("role");
}

bool Library::setRole(MediaPlayerGlobal::MediaRole role) {
    return setMetadata("role", role);
}

bool Library::isShared() const { return metaData<bool>("shared"); }

bool Library::setShared(bool shared) {
    auto ret = setMetadata("shared", shared);
    emit isSharedChanged();
    return ret;
}

QStringList Library::sourceDir() const {
    return metaData<QStringList>("sourceDir");
}

bool Library::addSourceDir(QString source) {
    auto t = sourceDir();
    if (source.startsWith("file:///"))
        source.remove(0, 8);

    bool ret = t.contains(source);
    t << source;
    t.removeDuplicates();
    setMetadata("sourceDir", t);
    emit sourceDirChanged();
    return !ret;
    ;
}

bool Library::removeSourceDir(QString source) {
    auto t = sourceDir();
    bool ret = t.indexOf(source) > -1;
    t.removeAt(t.indexOf(source));
    setMetadata("sourceDir", t);
    emit sourceDirChanged();
    return ret;
    ;
}

bool Library::addMedia(MediaPointer p) {
    m_medias[p->id()] = p;
    p->initFingerprint();
    connect(p.data(), &Media::mediaChanged, this, &Library::libraryChanged);
    connect(p.data(), &Media::mediaChanged, this, &Library::onMediaChanged);
    emit mediasChanged(p);
    return true;
}

bool Library::removeMedia(QString path) {
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly))
        return false;

    QCryptographicHash ch(QCryptographicHash::Md5);
    if (!ch.addData(&f))
        return false;

    auto md = ch.result();
    if (!m_pool.contains(md))
        return false;

    m_medias[m_pool[md]]->removePath(path);
    emit mediasChanged(m_medias[m_pool[md]]);
    return !m_medias[m_pool[md]]->paths().contains(path);
}

bool operator<(LibraryPointer l1, LibraryPointer l2) {
    return (l1->name() < l2->name()) || (l1->role() < l2->role());
}

int Library::mediaCount() const { return m_medias.count(); }

LibraryProbe *Library::probe() { return &m_probe; }

void Library::onProbedChanged() {
    if (m_probe.current() == 100.0)
        emit libraryChanged();
}

bool Library::addSmartPlaylist(SmartPlaylistPointer smart) {
    if(smart.isNull())
        return false;

    if (smart->id().isNull())
        smart->setId(QUuid::createUuid());

    auto ret = m_smartPlaylist.contains(smart->id());
    if (!ret) {
        connect(this, &Library::mediasChanged, smart.data(),
                &SmartPlaylist::onMediaChanged);
        m_smartPlaylist[smart->id()] = smart;
    }

    smart->set();
    connect(smart.data(), &PlayList::playlistChanged, this, &Library::libraryChanged);
    connect(smart.data(), &SmartPlaylist::rulesChanged, this, &Library::onSmartPlaylistChanged);

    emit playlistCountChanged();
    return !ret;
}

bool Library::removeSmartPlaylist(QString id) {
    auto ret = m_smartPlaylist.remove(QUuid::fromString(id)) > 0;
    emit playlistCountChanged();
    return ret;
}

QMap<QUuid, SmartPlaylistPointer> Library::smartPlaylist(QString id) {
    QMap<QUuid, SmartPlaylistPointer> ret;

    if (QUuid::fromString(id).isNull())
        ret = m_smartPlaylist;
    else
        ret[QUuid::fromString(id)] = m_smartPlaylist[QUuid::fromString(id)];

    return ret;
}

bool Library::addPlaylist(PlaylistPointer play) {
    if(play.isNull())
        return false;

    if (play->id().isNull())
        play->setId(QUuid::createUuid());

    auto ret = m_playlist.contains(play->id());
    if (!ret) {
        m_playlist[play->id()] = play;
    }
    play->set();
    connect(play.data(), &PlayList::playlistChanged, this, &Library::libraryChanged);

    emit playlistCountChanged();
    return !ret;
}

bool Library::removePlaylist(QString id) {
    auto ret = m_playlist.remove(QUuid::fromString(id)) > 0;
    emit playlistCountChanged();
    return ret;
}

QMap<QUuid, PlaylistPointer> Library::playlist(QString id) {
    QMap<QUuid, PlaylistPointer> ret;

    if (QUuid::fromString(id).isNull())
        ret = m_playlist;
    else
        ret[QUuid::fromString(id)] = m_playlist[QUuid::fromString(id)];

    return ret;
}

int Library::playlistCount() const {
    return m_playlist.count() + m_smartPlaylist.count();
}

void Library::onMediaChanged() {
    auto m = ((Media*)sender())->sharedFromThis();

    for(auto it: m_smartPlaylist)
        it->append(m);

    emit mediasChanged();
}

void Library::onSmartPlaylistChanged()
{
    auto smart = ((SmartPlaylist*)sender())->sharedFromThis().dynamicCast<SmartPlaylist>();

    for(auto it: m_medias) {
        smart->append(it);
    }
}

QList<PlayList*> Library::playlistList() const
{
    QList<PlayList*> ret;

    for(auto it: m_playlist)
        ret<<it.data();

    return ret;
}

bool Library::addToPlaylist(QString pl, Media* m)
{
    auto ppl = m_playlist[QUuid::fromString(pl)];

    return ppl->append(m->sharedFromThis()).result();
}

QList<MediaPlayerGlobal::Tag> Library::tags() const
{
    return metaData<QList<MediaPlayerGlobal::Tag>>("tags");
}

void Library::addTag(MediaPlayerGlobal::Tag t)
{
    QList<MediaPlayerGlobal::Tag> tagsList = tags();
    tagsList.append(t);
    setMetadata("tags", tagsList);
    emit libraryChanged();
}

void Library::editTag(MediaPlayerGlobal::Tag t)
{
    QList<MediaPlayerGlobal::Tag> tagsList = tags();
    auto f = std::find_if(tagsList.begin(), tagsList.end(), [t](auto it) {
        return it.first == t.first;
    });

    if(f != tagsList.end()) {
        f->second = t.second;
    }

    setMetadata("tags", tagsList);
    emit libraryChanged();
}

void Library::removeTag(MediaPlayerGlobal::Tag t)
{
    QList<MediaPlayerGlobal::Tag> tagsList = tags();
    std::remove_if(tagsList.begin(), tagsList.end(), [t](auto it) {
        return it.first == t.first;
    });

    setMetadata("tags", tagsList);
    emit libraryChanged();
}
