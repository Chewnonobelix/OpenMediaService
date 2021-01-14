#include "datajson.h"

DataJson::DataJson(const DataJson &dj) : InterfaceSaver(dj) {}

void DataJson::init() {}

QMap<QUuid, LibraryPointer> DataJson::selectLibrary() const {
	QDir dir;
	dir.cd("Library");

	auto libs = dir.entryInfoList({"*.json"});
	QMap<QUuid, LibraryPointer> ret;
	for (auto it : libs) {
		auto t = open(it.absoluteFilePath());
		ret[t->id()] = t;
	}
	return ret;
}

bool DataJson::createLibrary(QString name, MediaPlayerGlobal::MediaRole role) {
	auto l = factory<Library>();
	l->setId(QUuid::createUuid());
	l->setRole(role);
	l->setName(name);
	SmartPlaylistPointer all = factory<SmartPlaylist>();
	all->setName("All");
	l->addSmartPlaylist(all);

	write(l);
	emit librariesChanged();

	return true;
}

bool DataJson::removeLibrary(QUuid id) {
	QDir dir;
	dir.cd("Library");

	auto ret = QFile::remove(id.toString() + ".json");
	emit librariesChanged();

	return ret;
}

bool DataJson::updateLibrary(LibraryPointer l) {
	write(l);
	emit librariesChanged();
	return true;
}

LibraryPointer DataJson::open(QString path) const {
	QFile f(path);
	f.open(QIODevice::ReadOnly);
	auto data = f.readAll();
	QJsonDocument doc = QJsonDocument::fromJson(data);
	auto ret = factory<Library>(doc.object());
	f.close();

	return ret;
}

void DataJson::write(LibraryPointer l) const {
	QDir dir;
	dir.mkdir("Library");
	qDebug() << dir.cd("Library");
	qDebug() << l->id();
	QFile f("Library/" + l->id().toString() + ".json");
	f.open(QIODevice::WriteOnly);
	QJsonObject obj(*l);

	QJsonDocument doc(obj);
	f.write(doc.toJson());

	f.close();
}
