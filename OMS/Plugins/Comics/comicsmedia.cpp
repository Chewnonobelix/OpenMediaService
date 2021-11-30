#include "comicsmedia.h"

QProcess ComicsMedia::s_7z = QProcess();

ComicsMedia::ComicsMedia(MediaPointer media): m_base(media)
{
    auto p = m_base->path().split("/").last().split(".").first();
    if(!s_7z.program().contains("7z"))
        s_7z.setProgram("3rdParty/7z");
}

QImage ComicsMedia::cover() const
{
    QDir dir;
    dir.cd(m_extractDir->path());

    auto list = dir.entryInfoList({"*.jpg"});

    return !list.isEmpty() ? QImage(list[0].absoluteFilePath()) : QImage();
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

    s_7z.setArguments(QStringList()<<"x"<<"-o"+m_extractDir->path()<<m_base->path());
    s_7z.start();
    s_7z.waitForFinished();

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
