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
                                         {int(PlaylistRole::ListRole), "list"}};

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
    }

    return QVariant();
}

void ComicsPlaylist::init(PlaylistPointer pl)
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_stacks.clear();
    endRemoveRows();

    m_current = pl;

    for(auto it: *pl) {
        m_stacks[it->metaData<QString>(m_currentStackIndex, "Unknow")].medias<<it.data();
        m_stacks[it->metaData<QString>(m_currentStackIndex, "Unknow")].name = it->metaData<QString>(m_currentStackIndex);
    }

    beginInsertRows(QModelIndex(), 0, rowCount() - 1);
    endInsertRows();
}

void ComicsPlaylist::play(Media * media)
{
    auto smart = media->sharedFromThis();
    m_current->play(smart);
}
