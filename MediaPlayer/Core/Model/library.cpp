#include "library.h"

Library::Library() { set(); }

Library::Library(const Library &l) : QObject(nullptr), MetaData(l) { set(); }

Library::Library(QJsonObject &l) : QObject(nullptr), MetaData(l) {

	auto dirs = l["sourceDir"].toArray();
	auto ms = l["medias"].toArray();
	auto smarts = l["smartPlaylist"].toArray();
	auto plays = l["playlist"].toArray();

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

	m_probe.setLastProbed(
			QDateTime::fromString(l["lastProbe"].toString(), "dd-MM-yyyy hh:mm:ss"));

	set();
}

void Library::set() {
	connect(this, &Library::nameChanged, this, &Library::libraryChanged);
	connect(this, &Library::isSharedChanged, this, &Library::libraryChanged);
	connect(this, &Library::sourceDirChanged, this, &Library::libraryChanged);
	connect(this, &Library::lastUpdateChanged, this, &Library::libraryChanged);
	connect(this, &Library::playlistCountChanged, this, &Library::libraryChanged);
	connect(&m_probe, &LibraryProbe::mediaFind, this, &Library::addNMedia,
					Qt::QueuedConnection);
	connect(&m_probe, &LibraryProbe::currentChanged, this,
					&Library::onProbedChanged);
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

	return ret;
}

Library &Library::operator=(const Library &l) {
	MetaData &mt = *this;
	mt = l;
	return *this;
}

void Library::scan() {
	QSet<QString> paths;
	for (auto it : m_medias)
		for (auto it2 : it->paths())
			paths << it2;

	m_probe.setPaths(paths);
	m_probe.setSourceDir(sourceDir());
	m_probe.setRole(role());
	m_probe.probe();
}

QUuid Library::id() const { return metaData<QUuid>("id"); }

void Library::setId(QUuid id) { setMetadata("id", id); }

QString Library::name() const { return metaData<QString>("name"); }

void Library::setName(QString name) {
	setMetadata("name", name);
	emit nameChanged();
}

MediaPlayerGlobal::MediaRole Library::role() const {
	return metaData<MediaPlayerGlobal::MediaRole>("role");
}

void Library::setRole(MediaPlayerGlobal::MediaRole role) {
	setMetadata("role", role);
}

bool Library::isShared() const { return metaData<bool>("shared"); }

void Library::setShared(bool shared) {
	setMetadata("shared", shared);
	emit isSharedChanged();
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
	connect(p.data(), &Media::mediaChanged, this, &Library::libraryChanged);
	emit mediasChanged(p);
	return true;
}

bool Library::addNMedia(QString path, MD5 md) {
	if (md.isEmpty()) {
		QFile f(path);
		if (!f.open(QIODevice::ReadOnly))
			return false;

		QCryptographicHash ch(QCryptographicHash::Md5);
		if (!ch.addData(&f))
			return false;

		md = ch.result();
		f.close();
	}

	if (m_medias.contains(md))
		m_medias[md]->setPath(path);
	else if (MediaPlayerGlobal::getRole(path) == role())
		m_medias[md] = Media::createMedia(md, path);
	else
		return false;

	connect(m_medias[md].data(), &Media::mediaChanged, this,
					&Library::libraryChanged);

	return m_medias[md]->paths().contains(path);
}

bool Library::removeMedia(QString path) {
	QFile f(path);
	if (!f.open(QIODevice::ReadOnly))
		return false;

	QCryptographicHash ch(QCryptographicHash::Md5);
	if (!ch.addData(&f))
		return false;

	auto md = ch.result();
	if (!m_medias.contains(md))
		return false;

	m_medias[md]->removePath(path);
	emit mediasChanged(m_medias[md]);
	return !m_medias[md]->paths().contains(path);
}

bool operator<(LibraryPointer l1, LibraryPointer l2) {
	return (l1->name() < l2->name()) || (l1->role() < l2->role());
}

int Library::mediaCount() const { return m_medias.count(); }

LibraryProbe *Library::probe() { return &m_probe; }

void Library::onProbedChanged() {
	if (m_probe.current() == 100.0)
		emit mediasChanged();
}

bool Library::addSmartPlaylist(SmartPlaylistPointer smart) {
	if (smart->id().isNull())
		smart->setId(QUuid::createUuid());

	auto ret = m_smartPlaylist.contains(smart->id());
	if (!ret) {
		connect(this, &Library::mediasChanged, smart.data(),
						&SmartPlaylist::onMediaChanged);
		m_smartPlaylist[smart->id()] = smart;
	}

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
	if (play->id().isNull())
		play->setId(QUuid::createUuid());

	auto ret = m_playlist.contains(play->id());
	if (!ret) {
		m_playlist[play->id()] = play;
	}

	emit playlistCountChanged();
	return !ret;
}

bool Library::removePlaylist(QString id) {
	auto ret = m_playlist.remove(QUuid::fromString(id)) > 0;
	emit playlistCountChanged();
	return ret;
	;
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

void Library::onMediaChanged() { emit mediasChanged(); }
