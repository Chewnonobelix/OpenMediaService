#include "libraryprobe.h"

LibraryProbe::LibraryProbe(): QThread(nullptr)
{
    filter<<"*.mp3"<<"*.ogg"<<"*.flac"<<"*.cbr"<<"*.cbz"<<"*.pdf";
    connect(this, LibraryProbe::finished, this, LibraryProbe::onEnd);
}

LibraryProbe::LibraryProbe(const LibraryProbe& other): QThread(nullptr),
    baseName(other.baseName), filter(other.filter)
{
    connect(this, LibraryProbe::finished, this, LibraryProbe::onEnd);
}

LibraryProbe::~LibraryProbe()
{
}

QByteArray LibraryProbe::getMd5(QFileInfo info)
{
    QCryptographicHash ch(QCryptographicHash::Sha512);
    QFile f(info.absoluteFilePath());
    if(!f.open(QIODevice::ReadOnly))
        return "";
    
    ch.addData(&f);
    f.close();
    
    return ch.result().toHex();
}

QDateTime LibraryProbe::lastProbed() const
{
    return m_lastProbed;
}

void LibraryProbe::setLastProbed(QDateTime lastProbed)
{
    m_lastProbed = lastProbed;
}

void LibraryProbe::run()
{
    stat.setFileName("stat.txt");
    stat.open(QIODevice::WriteOnly);
    m_counter = 0;
    setLastProbed(QDateTime::currentDateTime());
    for(auto it: baseName)
        explore(it);
    
    QElapsedTimer t;
    t.start();
    int start = m_all.count();
    qDebug()<<"Start"<<m_all.count();
    qDebug()<<"base"<<baseName;
    while(m_all.count())
    {
        auto first = m_all.takeFirst();
        if(first.fileTime(QFileDevice::FileBirthTime) <= lastProbed() && first.fileTime(QFileDevice::FileModificationTime) <= lastProbed())
            continue;

        stat.write(QString("%1, %2\n").arg(((start - m_all.count())*100.0/start)).arg((start - m_all.count())).toLatin1());
        auto md = getMd5(first);
        emit s_add(md, first.absoluteFilePath());
        if((start - m_all.count()) % 2500 == 0)
        {
            double per = ((start - m_all.count())*100.0/start);
            qDebug()<<per;
        }
    }
    
    qDebug()<<"During"<<t.elapsed()/60;
}

void LibraryProbe::explore(QString dirName)
{
    qDebug()<<dirName;
    QDir dir(dirName);
    auto fl = dir.entryInfoList(filter);
    m_all.append(fl);
    
    m_counter += fl.size();
    
    
    auto subDirs = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
    qDebug()<<"Subs"<<subDirs;
    
    for(auto it: subDirs)
    {
        qDebug()<<lastProbed()<<it.lastModified()<<it.path();
        explore(it.absoluteFilePath());
    }
    
}

void LibraryProbe::onEnd()
{
    stat.close();
    qDebug()<<"Get "<<m_all.size();
}

bool LibraryProbe::hasProbed() const
{
    return m_counter != 0;
}
