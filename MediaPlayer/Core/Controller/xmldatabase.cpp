#include "xmldatabase.h"

XmlDatabase::XmlDatabase()
{
    
}

XmlDatabase::XmlDatabase(const XmlDatabase& xd): InterfaceSaver(xd)
{
    
}

XmlDatabase::~XmlDatabase()
{
    
    QDir dir = QDir::currentPath();
    if(!dir.exists("Library"))
        dir.mkdir("Library");
    
    QFile file("Library\\"+name()+".xml");
    
    if(!file.open(QIODevice::WriteOnly))
        return;

    qDebug()<<"To print"<<m_doc.toString().size();
    file.write(m_doc.toByteArray());    
    
    file.close();
}

void XmlDatabase::init()
{
    QFile file("Library\\"+name()+".xml");
    
    if(!file.open(QIODevice::ReadWrite))
        return;
    
    if(!m_doc.setContent(file.readAll()))
        qDebug()<<"Content"<<m_doc.setContent("<library role=\""+QString::number((int)role())+"\" />");
    else
    {
        int role = m_doc.documentElement().attribute("role").toInt();
        setRole((MediaRole)role);
    }
    
    file.close();
}

QDomElement XmlDatabase::adder(QDomElement& el, QString tagname, QString value, QMap<QString, QString> attr)
{
    QDomElement el3 = m_doc.createElement(tagname);
    QDomText txt = m_doc.createTextNode(value);
    el3.appendChild(txt);
    el.appendChild(el3);

    for(auto it = attr.begin(); it != attr.end(); it++)
        el3.setAttribute(it.key(), it.value());
    
    return el3;
}

void XmlDatabase::setter(QDomElement& el, QString tagname, QString value, QMap<QString, QString> attr)
{

    QDomElement child = el.elementsByTagName(tagname).at(0).toElement();
    if(child.isNull())
    {
        adder(el, tagname, value, attr);
        return;
    }
    
    QDomText txt = child.firstChild().toText();
    txt.setData(value);

    for(auto it = attr.begin(); it != attr.end(); it++)
        child.setAttribute(it.key(), it.key());
}

void XmlDatabase::deleter(QDomElement & el, QString tagname)
{
    auto old = el.elementsByTagName(tagname);
    for(int i = 0; i < old.size(); i++)
        el.removeChild(old.at(i).toElement());
    
}

void XmlDatabase::deleter(QDomElement & root, QDomElement& el)
{
    root.removeChild(el);
}


QMap<MD5, MediaPointer> XmlDatabase::selectMedia()
{
    QMap<MD5, MediaPointer> ret;
    
    auto root = m_doc.documentElement();
    
    auto list = root.elementsByTagName("media");
    qDebug()<<"Media size"<<list.size();
    for(int i = 0; i < list.size(); i++)
    {
        auto el = list.at(i).toElement();
        QString id = el.attribute("id");
        auto med = Media::createMedia(id.toLatin1());
        med->setRole(role());
        
        auto path = el.elementsByTagName("path");
        
        for(auto j = 0; j < path.size(); j++)
            med->setPath(path.at(j).toElement().text());
        
        med->setCount(el.elementsByTagName("counter").at(0).toElement().text().toInt());
        med->setAdded(QDate::fromString(el.elementsByTagName("added").at(0).toElement().text(), "dd-MM-yyy"));
        med->setLastFinish(QDateTime::fromString(el.elementsByTagName("lastFinish").at(0).toElement().text(), "hh:mm:ss dd-MM-yyy"));
        med->setCurrentRead(el.elementsByTagName("currentRead").at(0).toElement().text().toDouble());
        
        ret[id.toLatin1()] = med;
    }
    
    return ret;
}

bool XmlDatabase::addMedia(MediaPointer p)
{
//    qDebug()<<"Add "<<p->id();
    bool ret = false;
    
    auto root = m_doc.documentElement();
    QMap<QString, QString> attr;
    attr["id"] = p->id();
    auto el = adder(root, "media", "", attr);
    
    ret = !el.isNull();
    
    if(ret)
    {
        ret |= adder(el, "counter", QString::number(p->count())).isNull();
        ret |= adder(el, "currentRead", QString::number(p->currentRead())).isNull();
        ret |= adder(el, "added", p->added().toString("dd-MM-yyyy")).isNull();
        ret |= adder(el, "lastFinished", p->lastFinish().toString("hh:mm:ss dd-MM-yyyy")).isNull();
        
        for(auto it: p->paths())
            ret |= adder(el, "path", it).isNull();

    }        
    return ret;
}

bool XmlDatabase::removeMedia(MediaPointer p)
{
    auto root = m_doc.documentElement();
    auto list = root.elementsByTagName("media");
    bool ret = false;
    for(int i = 0; i < list.size(); i++)
        if((list.at(i).toElement().attribute("id").toLatin1() == p->id()))
        {
             auto el = list.at(i).toElement(); 
             deleter(root, el);
             ret = true;
        }
    return ret;
}

bool XmlDatabase::updateMedia(MediaPointer p)
{
    auto root = m_doc.documentElement();
    auto list = root.elementsByTagName("media");
    
    for(int i = 0; i < list.size(); i++)
    {
        QDomElement el = list.at(i).toElement();
        if(el.attribute("id").toLatin1() == p->id())
        {
            setter(el, "counter", QString::number(p->count()));
            setter(el, "lastFinished", p->lastFinish().toString("hh:mm:ss dd-MM-yyyy"));
            setter(el, "currentRead", QString::number(p->currentRead()));
            
            auto list2 = el.elementsByTagName("path");
            while(list2.size() > 0)
                el.removeChild(list2.at(0).toElement());
            
            for(auto it: p->paths())
            {
                if(it.isEmpty())
                    continue;

                adder(el, "path", it);      
            }
        }
    }
    return false;
}
