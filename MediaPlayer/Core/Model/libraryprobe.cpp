#include "libraryprobe.h"

LibraryProbe::LibraryProbe(): QThread(nullptr)
{
        filter<<"*.mp3"<<"*.ogg"<<"*.flac"<<"*.cbr"<<"*.cbz"<<"*.pdf";
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
    m_counter++;
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
    for(auto it: baseName)
        explore(it);
    
    QTime t;
    t.start();
    
    for(int i = 0; i < m_all.size(); i++)
    {
        auto md = getMd5(m_all[i]);
        emit s_add(md, m_all[i].absoluteFilePath());

        double per = (i*100.0/m_all.size());
        qDebug()<<per;
    }

    qDebug()<<"During"<<t.elapsed()/60;
}

void LibraryProbe::explore(QString dirName)
{
    qDebug()<<dirName;
    QDir dir(dirName);
    auto fl = dir.entryInfoList(filter);
    m_all.append(fl);

    
    auto subDirs = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
    
    
    for(auto it: subDirs)
    {
        qDebug()<<lastProbed()<<it.lastModified()<<it.path();
        if(it.lastModified() >= lastProbed() || it.created() > lastProbed())
            explore(it.absoluteFilePath());
        else
            qDebug()<<"Unprobe"<<it.absolutePath();
    }

}

void LibraryProbe::onEnd()
{
    qDebug()<<"Get "<<m_all.size();
}
