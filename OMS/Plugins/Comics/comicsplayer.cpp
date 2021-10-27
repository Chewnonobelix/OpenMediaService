#include "comicsplayer.h"

ComicsPlayer::~ComicsPlayer()
{
    if(m_dir)
        delete m_dir;
}

bool ComicsPlayer::play(MediaPointer m)
{
    QDir dir;
    if(m_dir)
        delete m_dir;

    auto p = m->path().split("\\").last().split(".").first();
    m_dir = new QTemporaryDir(p);

    QProcess unzipper;

    unzipper.start("7z", QStringList()<<"x"<<"-o"+m_dir->path()<<m->path());
    unzipper.waitForFinished();

    return m_dir->errorString().isEmpty();
}
