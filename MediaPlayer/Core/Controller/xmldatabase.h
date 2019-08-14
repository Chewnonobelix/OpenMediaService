#ifndef XMLDATABASE_H
#define XMLDATABASE_H

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QDir>
#include <QDebug>
#include "interfacesaver.h"

class XmlDatabase: public InterfaceSaver
{
    Q_OBJECT
    
private:
    QDomDocument m_doc;
    
    QDomElement adder(QDomElement&, QString , QString, QMap<QString, QString> = QMap<QString, QString>());
    void setter(QDomElement&, QString , QString, QMap<QString, QString> = QMap<QString, QString>() );
    void setter(QDomElement&, QString, QMap<QString, QString> = QMap<QString, QString>() );
    void deleter(QDomElement&, QString);
    void deleter(QDomElement&, QDomElement&);
    
public:
    XmlDatabase();
    XmlDatabase(const XmlDatabase&);
    ~XmlDatabase();
    
    virtual void init();
 
public slots:
    virtual QMap<MD5, MediaPointer> selectMedia();
    virtual bool addMedia(MediaPointer);
    virtual bool removeMedia(MediaPointer);
    virtual bool updateMedia(MediaPointer);
    
    virtual QSet<QString> selectSourceDir();
    virtual bool updateSourceDir(QSet<QString>);
    
    virtual QDateTime selectLastProbed();
    virtual bool updateLastProbed(QDateTime);
    
};

Q_DECLARE_METATYPE(XmlDatabase)
#endif // XMLDATABASE_H
