#ifndef DATAXML_HPP
#define DATAXML_HPP

#include "../Model/library.h"
#include "interfacesaver.h"
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QtCore/qglobal.h>

class DataXml : public InterfaceSaver
{
    Q_OBJECT
public:
    DataXml() = default;

    void init();

public slots:
    QMap<QUuid, LibraryPointer> selectLibrary(QUuid = QUuid()) const;
    LibraryPointer createLibrary(QString);
    bool removeLibrary(LibraryPointer);
    bool updateLibrary(LibraryPointer);

private:
    LibraryPointer openLibrary(QString) const;
};

#endif // DATAXML_HPP
