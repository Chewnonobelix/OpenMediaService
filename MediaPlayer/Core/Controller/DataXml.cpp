#include "DataXml.h"

void DataXml::init() {}

LibraryPointer DataXml::openLibrary(QString file) const
{
    LibraryPointer ret = LibraryPointer::create();
    QFile f(file);
    f.open(QIODevice::ReadOnly);
    QDomDocument doc;
    doc.setContent(&f);
    f.close();

    QDomElement el = doc.documentElement();
    ret->setId(QUuid::fromString(el.attribute("id")));
    ret->setName(el.attribute("name"));

    return ret;
}
QMap<QUuid, LibraryPointer> DataXml::selectLibrary(QUuid id) const
{
    QDir dir;
    dir.mkdir("Library");
    dir.cd("Library");
    QMap<QUuid, LibraryPointer> ret;
    auto list = dir.entryInfoList(QStringList("*.xml"));

    for (auto it : list) {
        if (id.isNull() || id == QUuid::fromString(it.baseName()))
            ret[it.baseName()] = openLibrary(it.absoluteFilePath());
    }
    return ret;
}

LibraryPointer DataXml::createLibrary(QString name)
{
    QDir dir;
    dir.mkdir("Library");

    dir.cd("Library");

    auto ret = LibraryPointer::create();
    ret->setId(QUuid::createUuid());
    ret->setName(name);

    if (dir.exists(ret->id().toString() + ".xml"))
        return LibraryPointer();

    QFile f("Library/" + ret->id().toString() + ".xml");
    qDebug() << "Open" << f.fileName() << f.open(QIODevice::ReadWrite);
    QDomDocument doc;
    doc.setContent(QString("<library />"));
    auto el = doc.documentElement();
    ;
    el.setAttribute("id", ret->id().toString());
    el.setAttribute("name", ret->name());
    f.write(doc.toString().toLatin1());
    f.close();
    return ret;
}

bool DataXml::removeLibrary(LibraryPointer l)
{
    QDir dir;
    dir.cd("Library");

    return dir.remove(l->id().toString() + ".xml");
}

bool DataXml::updateLibrary(LibraryPointer l)
{
    QFile f("Library/" + l->id().toString() + ".xml");
    bool ret = f.open(QIODevice::ReadWrite);
    QDomDocument doc;
    ret &= doc.setContent(&f);

    if (!ret)
        return ret;

    QDomElement el = doc.documentElement();
    el.setAttribute("name", l->name());
    f.write(doc.toByteArray());
    f.close();
    return true;
}
