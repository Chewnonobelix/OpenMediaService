#include "media.h"

Media::Media(MD5 id, QString path) : QObject(nullptr) {
	setId(id);
	if (!path.isEmpty())
		m_path << path;

	set();
}

Media::Media(const Media &other)
		: QObject(nullptr), MetaData(other),
			m_path(other.paths().begin(), other.paths().end()) {
	set();
}

Media::Media(QJsonObject &obj) : MetaData(obj) {
	auto sources = obj["sources"].toArray();

	for (auto it : sources)
		m_path << it.toString();
	set();
}

Media::operator QJsonObject() const {
	auto ret = MetaData::operator QJsonObject();

	QJsonArray sources;

	for (auto it : m_path)
		sources << it;

	ret["sources"] = sources;

	return ret;
}

void Media::set() {
	connect(this, &Media::countChanged, this, &Media::mediaChanged);
	connect(this, &Media::ratingChanged, this, &Media::mediaChanged);
	connect(this, &Media::currentReadChanged, this, &Media::mediaChanged);
	connect(this, &Media::lastFinishChanged, this, &Media::mediaChanged);
	connect(this, &Media::isAvailableChanged, this, &Media::mediaChanged);
	connect(this, &Media::lastProbedChanged, this, &Media::mediaChanged);
}

MD5 Media::id() const { return metaData<MD5>("id"); }

void Media::setId(MD5 id) { setMetadata("id", id); }

MediaPlayerGlobal::MediaRole Media::role() const {
	return metaData<MediaPlayerGlobal::MediaRole>("role");
}

void Media::setRole(MediaPlayerGlobal::MediaRole role) {
	setMetadata("role", role);
}

QString Media::path() const { return *m_path.begin(); }

QList<QString> Media::paths() const { return m_path.values(); }

void Media::setPath(QString path) {
	if (path.isEmpty())
		return;

	m_path << path;
	emit isAvailableChanged();
}

void Media::removePath(QString path) {
	m_path.remove(path);
	emit isAvailableChanged();
}

int Media::count() const {
	return hasMetadata("count") ? metaData<int>("count") : 0;
}

void Media::setCount(int count) {
	setMetadata("count", count);
	emit countChanged();
}

int Media::rating() const {
	return hasMetadata("rating") ? metaData<int>("rating") : 0;
}

void Media::setRating(int rate) {
	setMetadata("rating", rate);
	emit ratingChanged();
}

QDate Media::added() const { return metaData<QDate>("added"); }

void Media::setAdded(QDate added) { setMetadata("added", added); }

QDateTime Media::lastFinish() const {
	return metaData<QDateTime>("lastFinish");
}

void Media::setLastFinish(QDateTime lastFinish) {
	setMetadata("lastFinish", lastFinish);
	emit lastFinishChanged();
}

QDateTime Media::lastProbed() const {
	return metaData<QDateTime>("lastProbed");
}

void Media::setLastProbed(QDateTime lastProbed) {
	setMetadata("lastProbed", lastProbed);
	emit lastProbedChanged();
}

double Media::currentRead() const { return metaData<double>("currentRead"); }

void Media::setCurrentRead(double currentRead) {
	setMetadata("currentRead", currentRead);
	emit currentReadChanged();
}

MediaPointer Media::createMedia(MD5 id, QString path) {
	MediaPointer ret = factory<Media>(id, path);
	ret->setAdded(QDate::currentDate());
	ret->setRole(MediaPlayerGlobal::getRole(path));

	return ret;
}

int Media::nbPath() const { return m_path.size(); }

bool Media::isAvailable() const {
	bool ret = !m_path.isEmpty();
	for (auto it = m_path.begin(); ret && it != m_path.end(); it++)
		ret &= QFile::exists(*it);

	return ret;
}

Media &Media::operator=(const Media &other) {

	m_path.clear();
	for (auto it : other.paths())
		m_path << it;

	MetaData &mt = *this;
	mt = other;
	return *this;
}
