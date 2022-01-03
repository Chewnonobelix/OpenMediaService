#include "comicsplayer.h"

ComicsPlayer::ComicsPlayer(QObject* parent): QAbstractListModel(parent)
{}

ComicsPlayer::~ComicsPlayer()
{
}

bool ComicsPlayer::play(ComicsMedia m)
{
    m_media = m;
    if(!m_media.isLoad()) {
        m_media.load();
    }

    build();

    return m_media.isLoad();
}

void ComicsPlayer::build()
{
    if(!m_media.isLoad())
        return;

    QDir dir;
    dir.cd(m_media.dir()->path());
    auto ret = dir.cd("split");
    if(ret) {
        dir.removeRecursively();
        dir.cdUp();
    }

    dir.mkdir("split");
    m_pages.clear();

    auto list = dir.entryInfoList({"*.jpg"});
    QStringList working;

    for(auto it: list) {
        QImage i(it.absoluteFilePath());

        if(split() && i.width() > i.height()) {
            auto t1 = i.copy(0,0, i.width() / 2, i.height());
            auto t2 = i.copy(i.width() / 2,0, i.width() / 2, i.height());
            t1.save(dir.absolutePath()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(1));
            t2.save(dir.absolutePath()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(2));
            working<<(m_media.base()->metaData<bool>("rightToLeft") ? dir.absolutePath()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(2) : (dir.absolutePath()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(1)));
            working<<(m_media.base()->metaData<bool>("rightToLeft") ? dir.absolutePath()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(1) : (dir.absolutePath()+QString("/split/%1__%2.jpg").arg(it.baseName()).arg(2)));
        }
        else {
            working<<it.absoluteFilePath();
        }
    }

    m_pages = working;

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

    return QVariant();
}

bool ComicsPlayer::setData(const QModelIndex &, const QVariant &, int)
{
    return false;
}

int ComicsPlayer::currentPage() const
{
    auto name = m_media.base() ? m_media.base()->metaData<QString>("currentPage") : "";

    int ret = 0;
    auto file = name.split("/").last().split(".").first();
    QRegularExpression reg(".*"+file+".*");
    if(!name.isEmpty() && !m_pages.contains(reg) && split()) {
        ret = std::max(m_pages.indexOf(m_media.dir()->path()+"/split/"+file+"__1.jpg"), 0ll);
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
    if(m_media.base() && cp < m_pages.count() && cp >= 0) {
        m_media.base()->setMetadata("currentPage", m_pages[cp]);
        m_media.base()->setCurrentRead((cp + 1) / (double)m_pages.count() * 100.0);
        emit currentPageChanged();

        if(m_media.base()->currentRead() == 100.0)
            m_media.base()->setCount(m_media.base()->count() + 1);
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
    return m_media.base()->metaData<bool>("rightToLeft");
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

QStringList ComicsPlayer::pageTags(QString page) const
{
    auto p = baseName(page);
    return m_media.pageTag(p);
}

void ComicsPlayer::addPageTag(QString page, QString id)
{
    auto p = baseName(page);
    m_media.addPageTag(p, id);
}

void ComicsPlayer::removePageTag(QString page, QString id)
{
    auto p = baseName(page);
    m_media.removePageTag(p, id);
}


QStringList ComicsPlayer::bookmarks() const
{
    return m_media.bookmarks();
}

bool ComicsPlayer::addBookmark(QString b)
{
    auto base = baseName(b);
    return m_media.addBookmark(base);
}

bool ComicsPlayer::removeBookmark(QString b)
{
    return m_media.removeBookmark(b);
}

bool ComicsPlayer::loadBookmark(QString b)
{
    auto page = std::find_if(m_pages.begin(), m_pages.end(), [b](auto it) {
        return it.contains(b);
    });

    if(page != m_pages.end()) {
        auto index = std::distance(m_pages.begin(), page);
        setCurrentPage(index);
    }
    return false;
}

QString ComicsPlayer::baseName(QString page) const
{
    QString p;
    if(split() && page.contains("split")) {
        p = page.split("/").last().split("__").first();
    }
    else {
        p = page.split("/").last().split(".").first();
    }

    return p;
}
