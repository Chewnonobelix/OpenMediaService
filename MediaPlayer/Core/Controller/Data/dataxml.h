#ifndef DATAXML_HPP
#define DATAXML_HPP

#include "../../Model/global.h"
#include "../../Model/library.h"
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
    DataXml(const DataXml &) = default;
    void init();

public slots:
	QMap<QUuid, LibraryPointer> selectLibrary() const;
	bool createLibrary(QString, MediaPlayerGlobal::MediaRole);
	bool removeLibrary(QUuid);
    bool updateLibrary(QUuid);

private:
    LibraryPointer openLibrary(QString) const;
};

Q_DECLARE_METATYPE(DataXml)

#endif // DATAXML_HPP
