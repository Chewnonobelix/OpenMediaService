#include "DataXml.h"

void DataXml::init() {}

QMap<QUuid, LibraryPointer> DataXml::selectLibrary(QUuid) const
{
    return QMap<QUuid, LibraryPointer>();
}

LibraryPointer DataXml::createLibrary(QString)
{
    return LibraryPointer();
}

bool DataXml::removeLibrary(LibraryPointer)
{
    return false;
}

bool DataXml::updateLibrary(LibraryPointer)
{
    return false;
}
