#include "comicsplayer.h"

ComicsPlayer::ComicsPlayer(QObject* parent): QAbstractListModel(parent)
{}

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

    m_media = m;
    auto p = m->path().split("/").last().split(".").first();
    m_dir = new QTemporaryDir("temp/"+p);
    m_dir->setAutoRemove(true);
    QProcess unzipper;

    unzipper.start("7z", QStringList()<<"x"<<"-o"+m_dir->path()<<m->path());
    unzipper.waitForFinished();

    dir.cd(m_dir->path());
    m_pages.clear();
    auto list = dir.entryInfoList({"*.jpg"});
    for(auto it: list) {
        m_pages<<it.absoluteFilePath();
    }

    beginInsertRows(QModelIndex(), 0, rowCount() - 1);
    endInsertRows();
    emit pageCount();

    return m_dir->errorString().isEmpty();
}

int ComicsPlayer::rowCount(const QModelIndex& ) const
{
    return m_pages.count();
}

QHash<int, QByteArray> ComicsPlayer::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(ComicsPlayerRole::PageRole), "page"}};

    return ret;
}

QVariant ComicsPlayer::data(const QModelIndex& index, int role) const
{
    if(index.row() < 0 || index.row() >= rowCount())
       return QVariant();

    switch(ComicsPlayerRole(role)) {
    case ComicsPlayerRole::PageRole:
        return m_pages[index.row()];
    }
}
bool ComicsPlayer::setData(const QModelIndex &, const QVariant &, int)
{
    return false;
}

int ComicsPlayer::currentPage() const
{
    return m_media ? m_media->metaData<int>("currentPage"): 0;
}

void ComicsPlayer::setCurrentPage(int cp)
{
    if(m_media) {
        m_media->setMetadata("currentPage", cp);
        m_media->setCurrentRead((cp + 1) / (double)m_pages.count() * 100.0);
        emit currentPageChanged();
    }
}

int ComicsPlayer::pageCount() const
{
    return m_pages.count();
}
