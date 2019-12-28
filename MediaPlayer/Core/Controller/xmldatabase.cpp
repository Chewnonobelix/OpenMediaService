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

void XmlDatabase::setter(QDomElement& el, QString value, QMap<QString, QString> attr)
{
    QDomText txt = el.firstChild().toText();
    txt.setData(value);
    
    for(auto it = attr.begin(); it != attr.end(); it++)
        el.setAttribute(it.key(), it.key());
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

    for(int i = 0; i < list.size(); i++)
    {
        auto el = list.at(i).toElement();
        auto child = el.elementsByTagName("id").at(0).toElement();

        auto med = factory<Media>(child.text().toLatin1());

        
        auto path = el.elementsByTagName("path");
        
        for(auto j = 0; j < path.size(); j++)
            med->setPath(path.at(j).toElement().text());

        auto childs = el.childNodes();
        for(int j = 0; j < childs.size(); j++)
        {
            if(childs.at(j).toElement().tagName() != "path" && childs.at(j).toElement().tagName() != "id")
                med->setMetadata(childs.at(j).toElement().tagName(), childs.at(j).toElement().text());
        }
        
        ret[med->id()] = med;
    }
    
    return ret;
}

bool XmlDatabase::addMedia(MediaPointer p)
{
    bool ret = false;
    
    auto root = m_doc.documentElement();
    QMap<QString, QString> attr;

    auto el = adder(root, "media", "", attr);
    
    ret = !el.isNull();
    
    if(ret)
    {
        auto keys = p->metadataList();
        
        for(auto it: keys)
        {
            ret |= adder(el, it, p->metaData<QString>(it)).isNull();
        }
        
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
    {
        auto el1 = list.at(i).toElement();
        auto c = el1.elementsByTagName("id").at(0).toElement();
        if(c.text() == p->id())
        {
             auto el = list.at(i).toElement(); 
             deleter(root, el);
             ret = true;
        }
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
        auto el1 = list.at(i).toElement();
        auto c = el1.elementsByTagName("id").at(0).toElement();
        
        if(c.text() == p->id())
        {
            for(auto it: p->metadataList())
                setter(el, it,  p->metaData<QString>(it));
            
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

bool XmlDatabase::updateSourceDir(QSet<QString> sourceDir)
{
    auto root = m_doc.documentElement();
    auto list = root.elementsByTagName("sourceDir");
    
    if(sourceDir.size() != list.size())
    {
        while(list.size() != 0)
        {
            auto el = list.at(0).toElement();
            deleter(root, el);
        }
        
        for(auto it: sourceDir)
            adder(root, "sourceDir", it);
    }
    else
    {
        auto it = sourceDir.begin();
        for(int i = 0; i < list.size(); i++, it++)
        {
            auto el = list.at(i).toElement();
            setter(el, *it);
        }
    }
    
    return true;
}

bool XmlDatabase::updateLastProbed(QDateTime probed)
{
    auto root = m_doc.documentElement();
    auto list = root.elementsByTagName("lastProbed");
    
    if(list.size() == 0)
        adder(root, "lastProbed", probed.toString("hh:mm:ss dd-MM-yyyy"));
    else
        setter(root, "lastProbed", probed.toString("hh:mm:ss dd-MM-yyyy"));
    
    return true;
}

QDateTime XmlDatabase::selectLastProbed()
{
    auto root = m_doc.documentElement();
    auto list = root.elementsByTagName("lastProbed");

    return list.size() == 0 ? QDateTime() : QDateTime::fromString(list.at(0).toElement().text(), "hh:mm:ss dd-MM-yyyy");    
}

QSet<QString> XmlDatabase::selectSourceDir()
{
    QSet<QString> ret;
    auto root = m_doc.documentElement();
    auto list = root.elementsByTagName("sourceDir");
    
    for(int i = 0; i < list.size(); i++)
        ret<<list.at(i).toElement().text();
        
    return ret;
}
