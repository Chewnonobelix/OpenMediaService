#include "library.h"

Library::Library() {
	connect(&m_probe, &LibraryProbe::mediaFind, this, &Library::addMedia);
}

Library::Library(const Library &l) : QObject(nullptr), MetaData(l) {
	connect(&m_probe, &LibraryProbe::mediaFind, this, &Library::addMedia);
}

Library &Library::operator=(const Library &l) {
	MetaData &mt = *this;
	mt = l;
	return *this;
}

void Library::scan() {
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

QDateTime Library::lastProbed() const {
	return metaData<QDateTime>("lastProbed");
}

void Library::setLastProbed(QDateTime lp) {
	setMetadata("lastProbed", lp);
	emit lastProbedChanged();
}

QStringList Library::sourceDir() const {
	return metaData<QStringList>("sourceDir");
}

bool Library::addSourceDir(QString source) {
	auto t = sourceDir();
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

bool Library::addMedia(QString path, MD5 md) {
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

	emit mediasChanged();
	qDebug() << "Wesh" << path;
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
	emit mediasChanged();
	return !m_medias[md]->paths().contains(path);
}

QMap<MD5, MediaPointer> Library::medias(MD5 id) const {
	QMap<MD5, MediaPointer> ret;
	if (id.isEmpty())
		ret = m_medias;
	else
		ret[id] = m_medias[id];

	return ret;
}

bool operator<(LibraryPointer l1, LibraryPointer l2) {
	return (l1->name() < l2->name()) || (l1->role() < l2->role());
}

QDateTime Library::lastUpdate() const {
	return metaData<QDateTime>("lastUpdate");
}

void Library::setLastUpdate(QDateTime lastUpdate) {
	setMetadata("lastUpdate", lastUpdate);
	emit lastUpdateChanged();
}

int Library::mediaCount() const { return m_medias.count(); }

LibraryProbe *Library::probe() { return &m_probe; }
