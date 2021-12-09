#include "orderdisplaymodel.h"

OrderDisplayModel::OrderDisplayModel(QObject* parent): QAbstractListModel(parent)
{

}

QVariant OrderDisplayModel::data(const QModelIndex & index, int role) const
{
    if(index.row() < 0 && index.row() >= rowCount())
        return QVariant();

    switch(OrderRole(role)) {
    case OrderRole::DisplayRole:
        return (*m_playlist)[m_playlist->readOrder()[index.row()]]->path();
    case OrderRole::IndexRole:
        return m_playlist->readOrder()[index.row()];
    case OrderRole::CurrentIndexRole:
        return m_playlist->currentIndex();
    }

    return QVariant();
}

int OrderDisplayModel::rowCount(const QModelIndex &) const
{
    return m_playlist->readOrder().count();
}

QHash<int, QByteArray> OrderDisplayModel::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(OrderRole::DisplayRole), "display"},
                                         {int(OrderRole::IndexRole), "playlistIndex"},
                                         {int(OrderRole::CurrentIndexRole), "currentIndex"}};

    return ret;
}

void OrderDisplayModel::setPlaylist(PlaylistPointer pl)
{
    m_playlist = pl;
}
