#include "libraryprobe.h"

QSet<QByteArray> LibraryProbe::global = QSet<QByteArray>();
int LibraryProbe::globalCount = 0;

void LibraryProbe::onEnd()
{
    global+= md5;
    globalCount += counter;

    qDebug()<<"Finish"<<baseName<<counter<<md5.size()<<globalCount<<global.size();
}

LibraryProbe::LibraryProbe(): counter(0)
{
        filter<<"*.mp3"<<"*.ogg"<<"*.flac"<<"*.cbr"<<"*.cbz"<<"*.pdf";
        connect(this, LibraryProbe::finished, this, LibraryProbe::onEnd);
}

LibraryProbe::~LibraryProbe()
{
    qDebug()<<"Finish"<<baseName<<counter<<md5.size();
}

QByteArray LibraryProbe::getMd5(QFileInfo info)
{
    QCryptographicHash ch(QCryptographicHash::Md5);
    QFile f(info.absoluteFilePath());
    if(!f.open(QIODevice::ReadOnly))
        return "";
    
    ch.addData(&f);
    f.close();
    counter++;
    return ch.result().toHex();    
}

void LibraryProbe::run()
{
    for(auto it: baseName)
        explore(it);
}

void LibraryProbe::explore(QString dirName)
{
//    qDebug()<<"Explore"<<dirName;
    QDir dir(dirName);
    auto fl = dir.entryInfoList(filter);
    for(auto it: fl)
    {
        auto md = getMd5(it);
        if(md5.contains(md))
            qDebug()<<it;
        qDebug()<<it.baseName()<<md;
        md5<<md;
    }
    
    auto subDirs = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
    
    
    for(auto it: subDirs)
    {
//        qDebug()<<it.absoluteFilePath();
        explore(it.absoluteFilePath());
    }

//    qDebug()<<"End"<<dirName;
}
