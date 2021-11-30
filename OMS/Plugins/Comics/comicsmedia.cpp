#include "comicsmedia.h"


ComicsMedia::ComicsMedia(MediaPointer media): m_base(media)
{
}

QImage ComicsMedia::cover() const
{
    QDir dir;
    dir.cd("cache");

    auto list = dir.entryInfoList({QString("%1.*").arg(m_base->id().toString())});
    QString ret;
    if(list.isEmpty()) {
        QProcess uz;
        uz.setProgram("3rdParty/7z");
        uz.setArguments({"l", m_base->path()});
        uz.start();
        uz.waitForFinished();
        auto lines = QString(uz.readAllStandardOutput()).split('\n');
        auto first = lines[lines.indexOf(QRegularExpression(".*jpg.*"))];
        auto fileName = first.split(' ').last().remove('\r');

        uz.setArguments({"e", QString("-i!%1").arg(fileName), m_base->path(), "-otemp/*"});
        uz.start();
        uz.waitForFinished();
        QFileInfo info(m_base->path());
        auto base = info.baseName();
        QFile file(QString("temp/%1/%2").arg(base).arg(fileName));
        ret = QString("cache/%1.%2").arg(m_base->id().toString()).arg(fileName.split('.').last());
        file.copy(ret);
    }
    else
    {
        ret = list[0].absoluteFilePath();
    }

    return QImage(ret);
}

QSharedPointer<QTemporaryDir> ComicsMedia::dir() const
{
    return m_extractDir;
}

void ComicsMedia::load()
{
    auto p = m_base->path().split("/").last().split(".").first();
    m_extractDir = factory<QTemporaryDir>("temp/"+p);

    m_extractDir->setAutoRemove(false);
    QProcess uz;

    uz.setProgram("3rdParty/7z");
    uz.setArguments(QStringList()<<"x"<<"-o"+m_extractDir->path()<<m_base->path());
    uz.start();
    uz.waitForFinished();

    QDir dir;
    dir.cd(m_extractDir->path());
    dir.mkdir("split");

    auto list = dir.entryInfoList({"*.jpg"});

    for(auto it: list) {
        QImage i(it.absoluteFilePath());

        if(i.width() > i.height()) {
            auto t1 = i.copy(0,0, i.width() / 2, i.height());
            auto t2 = i.copy(i.width() / 2,0, i.width() / 2, i.height());
            t1.save(m_extractDir->path()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(1));
            t2.save(m_extractDir->path()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(2));
        }
    }
}

void ComicsMedia::unload()
{
    m_extractDir.clear();
}

MediaPointer ComicsMedia::base() const
{
    return m_base;
}
