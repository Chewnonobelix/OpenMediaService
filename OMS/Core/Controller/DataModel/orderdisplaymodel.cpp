#include "orderdisplaymodel.h"

OrderDisplayModel::OrderDisplayModel(QObject* parent): QAbstractListModel(parent)
{

}

QVariant OrderDisplayModel::data(const QModelIndex & index, int role) const
{
    if(index.row() < 0 || index.row() >= rowCount())
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
    return m_playlist ? m_playlist->readOrder().count() : 0;
}

QHash<int, QByteArray> OrderDisplayModel::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(OrderRole::DisplayRole), "path"},
                                         {int(OrderRole::IndexRole), "playlistIndex"},
                                         {int(OrderRole::CurrentIndexRole), "currentIndex"}};

    return ret;
}

void OrderDisplayModel::setPlaylist(PlaylistPointer pl)
{
    if(m_playlist) {
        beginRemoveRows(QModelIndex(), 0, m_playlist->readOrder().count());
        endRemoveRows();
        disconnect(m_playlist.data(), &PlayList::currentIndexChanged, this, &OrderDisplayModel::onReadOrderChanged);
    }

    m_playlist = pl;

    if(m_playlist) {
        connect(m_playlist.data(), &PlayList::currentIndexChanged, this, &OrderDisplayModel::onReadOrderChanged);
        beginInsertRows(QModelIndex(), 0, m_playlist->readOrder().count() - 1);
        endInsertRows();
    }

}

void OrderDisplayModel::onReadOrderChanged()
{
    beginResetModel();
    endResetModel();
}
