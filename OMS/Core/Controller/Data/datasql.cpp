#include "datasql.h"

DataSql::DataSql(const DataSql& data): InterfaceSaver(data)
{}

DataSql::~DataSql()
{
    if(m_db.isOpen()) {
        m_db.close();
    }
}

QMap<QUuid, LibraryPointer> DataSql::selectLibrary() const
{
    auto ret = QMap<QUuid, LibraryPointer>();
    if(m_db.isOpen()) {
        auto res = m_db.exec("SELECT * FROM library");
        qDebug()<<res.lastError();

        while(res.next()) {
            LibraryPointer l = LibraryPointer::create();
            l->setId(QUuid::fromString(res.value("id").toString().replace("\\{", "{")));
            l->setName(res.value("name").toString());
            l->setRole(MediaRole(res.value("role").toInt()));

            qDebug()<<res.value("id");
            ret[l->id()] = l;
        }
    }
    return ret;
}

bool DataSql::createLibrary(QString name, MediaPlayerGlobal::MediaRole role)
{
    auto l = factory<Library>();
    l->setId(QUuid::createUuid());
    l->setRole(role);
    l->setName(name);
    SmartPlaylistPointer all = factory<SmartPlaylist>();
    all->setName("All");
    l->addSmartPlaylist(all);

    auto idString = [](auto id) {
        auto ret = id.toString();
        ret = ret.replace("{", "\\{");
        return ret;
    };

    if(m_db.isOpen()) {
        auto res = m_db.exec(QString("INSERT INTO library (id, name, role, isShared) VALUES ('%1', '%2', '%3', false)")
                                 .arg(idString(l->id())).arg(l->name()).arg(int(l->role())));

        qDebug()<<res.lastError()<<res.lastQuery();

        if(res.isValid())
            emit librariesChanged();

        return res.isValid();
    }
    return false;
}

bool DataSql::removeLibrary(QString)
{
    return false;
}

bool DataSql::updateLibrary(LibraryPointer)
{
    return false;
}

void DataSql::init()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", "default");
    m_db.setDatabaseName("oms");
    m_db.open();
    qDebug()<<"SQL Database"<<m_db.connectionName()<<m_db.isOpen();
    auto res = m_db.exec("SELECT * FROM library");
    qDebug()<<res.lastError()<<res.size();
}
