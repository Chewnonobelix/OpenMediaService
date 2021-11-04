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
    if(m_dir)
        delete m_dir;

    m_media = m;
    auto p = m->path().split("/").last().split(".").first();
    m_dir = new QTemporaryDir("temp/"+p);
    m_dir->setAutoRemove(true);
    QProcess unzipper;

    unzipper.start("3rdParty/7z", QStringList()<<"x"<<"-o"+m_dir->path()<<m->path());
    unzipper.waitForFinished();

    build();

    return m_dir->errorString().isEmpty();
}

void ComicsPlayer::build()
{
    if(!m_dir)
        return;

    QDir dir;
    dir.cd(m_dir->path());
    auto ret = dir.cd("split");
    if(ret) {
        dir.removeRecursively();
        dir.cdUp();
    }

    dir.mkdir("split");
    m_pages.clear();

    auto list = dir.entryInfoList({"*.jpg"});
    for(auto it: list) {
        QImage i(it.absoluteFilePath());

        if(split() && i.width() > i.height()) {
            auto t1 = i.copy(0,0, i.width() / 2, i.height());
            auto t2 = i.copy(i.width() / 2,0, i.width() / 2, i.height());
            t1.save(m_dir->path()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(1));
            t2.save(m_dir->path()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(2));
            m_pages<<(m_media->metaData<bool>("rightToLeft") ? m_dir->path()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(2) : m_dir->path()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(1));
            m_pages<<(m_media->metaData<bool>("rightToLeft") ? m_dir->path()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(1) : m_dir->path()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(2));
        }
        else {
            m_pages<<it.absoluteFilePath();
        }
    }

    beginInsertRows(QModelIndex(), 0, rowCount() - 1);
    endInsertRows();
    emit pageCount();
    emit currentPageChanged();

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
    auto name = m_media ? m_media->metaData<QString>("currentPage") : "";

    int ret = 0;
    auto file = name.split("/").last().split(".").first();
    QRegularExpression reg(".*"+file+".*");
    if(!name.isEmpty() && !m_pages.contains(reg) && split()) {
        ret = std::max(m_pages.indexOf(m_dir->path()+"/split/"+file+"__1.jpg"), 0ll);
    }
    else if(!name.isEmpty() && !m_pages.contains(reg)) {
        ret = std::max(m_pages.indexOf(QRegularExpression(".*"+file.split("__").first()+".*")), 0ll);
    }
    else if(m_pages.contains(reg)) {
        ret = m_pages.indexOf(reg);
    }

    return ret;
}

void ComicsPlayer::setCurrentPage(int cp)
{
    if(m_media && cp < m_pages.count() && cp >= 0) {
        m_media->setMetadata("currentPage", m_pages[cp]);
        m_media->setCurrentRead((cp + 1) / (double)m_pages.count() * 100.0);
        emit currentPageChanged();
    }
}

int ComicsPlayer::pageCount() const
{
    return m_pages.count();
}

void ComicsPlayer::next()
{
    setCurrentPage(currentPage() + 1);
}

void ComicsPlayer::previous()
{
    setCurrentPage(currentPage() - 1);
}

bool ComicsPlayer::rightToLeft() const
{
    return m_media->metaData<bool>("rightToLeft");
}

bool ComicsPlayer::split() const
{
    return m_split;
}

void ComicsPlayer::setSplit(bool split)
{
    m_split = split;
    emit splitChanged();
    build();
}
