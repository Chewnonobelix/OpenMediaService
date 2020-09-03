#ifndef DATAXML_HPP
#define DATAXML_HPP

#include "interfacesaver.h"
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
};

#endif // DATAXML_HPP
