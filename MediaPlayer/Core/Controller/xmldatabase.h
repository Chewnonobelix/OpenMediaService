#ifndef XMLDATABASE_H
#define XMLDATABASE_H

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QDebug>
#include "interfacesaver.h"

class XmlDatabase: public InterfaceSaver
{
private:
    QDomDocument m_doc;
    
    QDomElement adder(QDomElement&, QString , QString, QMap<QString, QString> = QMap<QString, QString>());
    void setter(QDomElement&, QString , QString, QMap<QString, QString> = QMap<QString, QString>() );
    void deleter(QDomElement&, QString);
    void deleter(QDomElement&, QDomElement&);
    
public:
    XmlDatabase();
    
    virtual void init();
    
    virtual QMap<MD5, MediaPointer> selectMedia();
    virtual bool addMedia(MediaPointer);
    virtual bool removeMedia(MediaPointer);
    virtual bool updateMedia(MediaPointer);
    
};

Q_DECLARE_METATYPE(XmlDatabase)
#endif // XMLDATABASE_H
