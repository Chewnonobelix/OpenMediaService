#include "DataXml.h"

void DataXml::init() {}

void DataXml::adder(QDomElement &el, QString tagname, QString value,
										QMap<QString, QString> attr) {
	QDomElement el3 = m_currentDoc.createElement(tagname);
	QDomText txt = m_currentDoc.createTextNode(value);
	el3.appendChild(txt);
	el.appendChild(el3);

	for (auto it = attr.begin(); it != attr.end(); it++)
		el3.setAttribute(it.key(), it.value());
}

void DataXml::setter(QDomElement &el, QString tagname, QString value,
										 QMap<QString, QString> attr) {
	QDomElement child = el.elementsByTagName(tagname).at(0).toElement();

	el.removeChild(child);
	adder(el, tagname, value, attr);
}

void DataXml::deleter(QDomElement &el, QString tagname) {
	auto old = el.elementsByTagName(tagname);
	if (old.size() == 1)
		el.removeChild(old.at(0));
}

LibraryPointer DataXml::openLibrary(QString file) const {
	LibraryPointer ret = LibraryPointer::create();
	QFile f(file);
	f.open(QIODevice::ReadOnly);
	QDomDocument doc;
	doc.setContent(&f);
	f.close();

	QDomElement el = doc.documentElement();
	ret->setId(QUuid::fromString(el.attribute("id")));
	ret->setName(el.attribute("name"));
	ret->setRole((MediaPlayerGlobal::MediaRole)el.attribute("role").toInt());
	auto sources = el.elementsByTagName("sourceDir");

	for (auto i = 0; i < sources.size(); i++) {
		auto child = sources.at(i).toElement();
		ret->addSourceDir(child.text());
	}

	return ret;
}
QMap<QUuid, LibraryPointer> DataXml::selectLibrary() const {
	QDir dir;
	dir.mkdir("Library");
	dir.cd("Library");
	QMap<QUuid, LibraryPointer> ret;
	auto list = dir.entryInfoList(QStringList("*.xml"));

	for (auto it : list) {
		auto lib = openLibrary(it.absoluteFilePath());
		ret[lib->id()] = lib;
	}

	return ret;
}

bool DataXml::createLibrary(QString name, MediaRole role) {
	QDir dir;
	dir.mkdir("Library");

	dir.cd("Library");

	auto ret = LibraryPointer::create();
	ret->setId(QUuid::createUuid());
	ret->setName(name);
	ret->setRole(role);
	if (dir.exists(ret->id().toString() + ".xml"))
		return false;

	QFile f("Library/" + ret->id().toString() + ".xml");
	qDebug() << "Open" << f.fileName() << f.open(QIODevice::ReadWrite);
	QDomDocument doc;
	doc.setContent(QString("<library />"));
	auto el = doc.documentElement();
	;
	el.setAttribute("id", ret->id().toString());
	el.setAttribute("name", ret->name());
	el.setAttribute("role", QString::number((int)ret->role()));

	f.write(doc.toString().toLatin1());
	f.close();

	emit librariesChanged();
	return !ret.isNull();
}

bool DataXml::removeLibrary(QUuid l) {
	QDir dir;
	dir.cd("Library");
	auto ret = dir.remove(l.toString() + ".xml");

	emit librariesChanged();

	return ret;
}

bool DataXml::updateLibrary(LibraryPointer lid) {
	QFile f("Library/" + lid->id().toString() + ".xml");
	bool ret = f.open(QIODevice::ReadWrite);
	QDomDocument doc;
	ret &= doc.setContent(&f);

	if (!ret)
		return ret;

	QDomElement el = doc.documentElement();
	m_currentDoc = doc;
	el.setAttribute("name", lid->name());
	auto sources = el.elementsByTagName("sourceDir");
	while (sources.size() > 0)
		el.removeChild(sources.at(0));

	for (auto it : lid->sourceDir())
		adder(el, "sourceDir", it);

	f.seek(0);
	f.write(doc.toByteArray());
	f.close();

	emit librariesChanged();
	return true;
}
