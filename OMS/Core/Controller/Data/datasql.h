#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>

#include <Controller/Data/interfacesaver.h>

#include <Model/library.h>
#include <Model/media.h>
#include <Model/smartplaylist.h>

class DataSql: public InterfaceSaver
{
public:
    DataSql() = default;
    DataSql(const DataSql &);
    ~DataSql() override = default;

    virtual void init() = 0;

public slots:
    QMap<QUuid, LibraryPointer> selectLibrary() const override;
    bool createLibrary(QString, MediaPlayerGlobal::MediaRole) override;
    bool removeLibrary(QString) override;
    bool updateLibrary(LibraryPointer) override;
};

