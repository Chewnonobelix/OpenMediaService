#include "datasql.h"

DataSql::DataSql(const DataSql& data): InterfaceSaver(data)
{}

QMap<QUuid, LibraryPointer> DataSql::selectLibrary() const
{
    return QMap<QUuid, LibraryPointer>();
}

bool DataSql::createLibrary(QString, MediaPlayerGlobal::MediaRole)
{
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
