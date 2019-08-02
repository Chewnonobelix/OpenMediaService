#include "libraryprobe.h"

LibraryProbe::LibraryProbe(): counter(0)
{
        filter<<"*.mp3";
}

LibraryProbe::~LibraryProbe()
{
    qDebug()<<"Finish"<<counter<<md5.size();
}

QByteArray LibraryProbe::getMd5(QFileInfo info)
{
    QCryptographicHash ch(QCryptographicHash::Sha512);
    QFile f(info.absoluteFilePath());
    if(!f.open(QIODevice::ReadOnly))
        return "";
    
    ch.addData(&f);
    f.close();
    counter++;
    return ch.result().toHex();    
}

void LibraryProbe::explore(QString dirName)
{
    qDebug()<<"Explore"<<dirName;
    QDir dir(dirName);
    auto fl = dir.entryInfoList(filter);
    for(auto it: fl)
    {
        auto md = getMd5(it);
        qDebug()<<it.baseName()<<md<<md.size();
        md5<<md;
    }
    
    auto subDirs = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
    
    
    for(auto it: subDirs)
    {
        qDebug()<<it.absoluteFilePath();
        explore(it.absoluteFilePath());
    }
}
