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
    void init() override;

public slots:
    QMap<QUuid, LibraryPointer> selectLibrary() const override;
    bool createLibrary(QString, MediaPlayerGlobal::MediaRole) override;
    bool removeLibrary(QUuid) override;
    bool updateLibrary(LibraryPointer) override;

private:
	LibraryPointer openLibrary(QString) const;
	QDomDocument m_currentDoc;
	void deleter(QDomElement &, QString);
	void setter(QDomElement &, QString, QString, QMap<QString, QString> = QMap<QString, QString>());
	void adder(QDomElement &, QString, QString, QMap<QString, QString> = QMap<QString, QString>());
};

Q_DECLARE_METATYPE(DataXml)

#endif // DATAXML_HPP
