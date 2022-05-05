#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <Controller/Data/interfacesaver.h>

#include <Model/library.h>
#include <Model/media.h>
#include <Model/smartplaylist.h>

class DataSql: public InterfaceSaver
{
private:
    QSqlDatabase m_db;

public:
    DataSql() = default;
    DataSql(const DataSql &);
    ~DataSql() override;

    virtual void init() override;

public slots:
    QMap<QUuid, LibraryPointer> selectLibrary() const override;
    bool createLibrary(QString, MediaPlayerGlobal::MediaRole) override;
    bool removeLibrary(QString) override;
    bool updateLibrary(LibraryPointer) override;
};

