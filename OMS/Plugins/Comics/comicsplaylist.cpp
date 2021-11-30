#include "comicsplaylist.h"

ComicsPlaylist::ComicsPlaylist(QObject * parent): QAbstractListModel(parent)
{

}

int ComicsPlaylist::rowCount(const QModelIndex &) const
{
    return m_stacks.count();
}

QHash<int, QByteArray> ComicsPlaylist::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(PlaylistRole::NameRole), "name"},
                                         {int(PlaylistRole::ListRole), "list"},
                                         {int(PlaylistRole::CoverRole), "cover"}};

    return ret;
}

QVariant ComicsPlaylist::data(const QModelIndex & index, int role) const
{
    if(index.row() < 0 || index.row() >= rowCount()) {
        return QVariant();
    }

    auto erole = PlaylistRole(role);

    switch (erole) {
    case PlaylistRole::NameRole:
        return m_stacks.keys()[index.row()];
        break;
    case PlaylistRole::ListRole:
        return QVariant::fromValue(m_stacks[m_stacks.keys()[index.row()]].medias);
        break;
    case PlaylistRole::CoverRole:
        return "file:///"+m_stacks[m_stacks.keys()[index.row()]].mini;
        break;
    }

    return QVariant();
}

void ComicsPlaylist::init(PlaylistPointer p, QList<ComicsMedia> pl)
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_stacks.clear();
    endRemoveRows();

    m_current = p;

    for(auto it: pl) {
        auto m = it.base();
        m_stacks[m->metaData<QString>(m_currentStackIndex, "Unknow")].medias<<m.data();
        m_stacks[m->metaData<QString>(m_currentStackIndex, "Unknow")].name = m->metaData<QString>(m_currentStackIndex);
        it.load();
        if(m_stacks[m->metaData<QString>(m_currentStackIndex, "Unknow")].mini.isNull()) {
            m_stacks[m->metaData<QString>(m_currentStackIndex, "Unknow")].mini = it.cover();
        }
    }


    beginInsertRows(QModelIndex(), 0, rowCount() - 1);
    endInsertRows();
}

void ComicsPlaylist::play(Media * media)
{
    auto smart = media->sharedFromThis();
    m_current->play(smart);
}

bool ComicsPlaylist::split() const
{
    return m_split;
}

void ComicsPlaylist::setSplit(bool s)
{
    m_split = s;
}
