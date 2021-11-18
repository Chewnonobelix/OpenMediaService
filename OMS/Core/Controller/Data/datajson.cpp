#include "datajson.h"

DataJson::DataJson(const DataJson &dj) : InterfaceSaver(dj) {}

DataJson::~DataJson()
{
    timerEvent(nullptr);
}

void DataJson::init()
{
    startTimer(3*60*1000);
}


void DataJson::timerEvent(QTimerEvent *)
{
    while(!m_pool.isEmpty()) {
        auto it = m_pool.dequeue();
        qDebug()<<"Dequeu"<<m_pool.count()<<m_pool.isEmpty();
        write(it);
    }
}

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

bool DataJson::removeLibrary(QString id) {
    QDir dir;
    dir.cd("Library");

    auto ret = QFile::remove("Library/" + id + ".json");
    emit librariesChanged();

    return ret;
}

bool DataJson::updateLibrary(LibraryPointer l) {
    if(!m_pool.contains(l))
        m_pool.enqueue(l);

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
    dir.cd("Library");
    QFile f("Library/" + l->id().toString() + ".json");
    f.open(QIODevice::WriteOnly);
    QJsonObject obj(*l);

    QJsonDocument doc(obj);
    f.write(doc.toJson());

    f.close();
}
