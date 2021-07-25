#include "playlistlistmodel.h"

void PlaylistListModel::setPlaylist(PlaylistPointer p)
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    removeRows(0, rowCount());
    endRemoveRows();
    beginRemoveColumns(QModelIndex(), 0, columnCount());
    removeColumns(0, columnCount());
    endRemoveColumns();

    m_model = p;

    beginInsertRows(QModelIndex(), 0, rowCount());
    insertRows(0, rowCount());
    endInsertRows();
    beginInsertColumns(QModelIndex(), 0, columnCount());
    insertColumns(0, columnCount());
    endInsertColumns();

    m_sortList.clear();
    if(p)
        for(auto it = 0; it < p->count(); it++)
            m_sortList<<it;

    sort(0);
}

int PlaylistListModel::rowCount(const QModelIndex&) const
{
    return m_sortList.size();
}

int PlaylistListModel::columnCount(const QModelIndex&) const {
    return m_columns.size();
}

QVariant PlaylistListModel::data(const QModelIndex& index, int role) const {
    auto row = index.row(), col = index.column();

    if((row < 0 || row >= rowCount()) || (col < 0 || col >= columnCount()))
        return QVariant();

    auto current = (*m_model)[m_sortList[row]];
    auto currentCol = m_columns[col];

    if(role < int(ImageListRole::FileRole)) {
        switch(currentCol.role) {
        case ImageListRole::FileRole:
            return current->path().split("/").last();
            break;
        case ImageListRole::PathRole: {
            auto last = current->path().lastIndexOf("/");
            return current->path().mid(0, last);
        }
            break;
        case ImageListRole::CountRole:
            return current->count();
            break;
        case ImageListRole::AddedRole:
            return current->added().toString("dd-MM-yyyy");
            break;
        case ImageListRole::LastPlayRole:
            return current->lastFinish().toString("dd-MM-yyyy hh:mm:ss");
            break;
        case ImageListRole::ExtensionRole: {
            auto last = current->path().lastIndexOf(".");
            return current->path().mid(last);
            break;
        }
        case ImageListRole::RatingRole:
            return current->rating();
            break;
        case ImageListRole::OrderRole:
            return QVariant::fromValue(current->role());
        default:
            break;
        }
    }

    auto erole = ImageListRole(role);
    switch(erole) {
    case ImageListRole::Fullpath:
        return current->path();
    case ImageListRole::IndexRole:
        return m_model->indexOf(current);
    case ImageListRole::EnableRole:
        return currentCol.enable;
    case ImageListRole::OrderRole:
        return QVariant::fromValue(current->role());
    default:
        break;
    }

    return QVariant();
}
void PlaylistListModel::sort(int col, TristateOrder order) {
    for(auto& it: m_columns)
        it.order = TristateOrder::NoOrder;
    m_columns[col].order = order;

    for(auto i = 0; i < m_sortList.count(); i ++)
    {
        auto mi = (*m_model)[m_sortList[i]];
        for(auto j = i; j < m_sortList.count(); j++) {
            auto mj = (*m_model)[m_sortList[j]];

            switch (m_columns[col].order) {
            case TristateOrder::AscendingOrder:
                if(compare(mi, mj, m_columns[col].name) != Media::CompareState::SuperiorState)
                {
                    m_sortList.swapItemsAt(i, j);
                    mi = mj;
                }
                break;
            case TristateOrder::DescendingOrder:
                if(compare(mi, mj, m_columns[col].name) != Media::CompareState::InferiorState)
                {
                    m_sortList.swapItemsAt(i, j);
                    mi = mj;
                }
                break;
            default:
                if(m_sortList[j] < m_sortList[i]){
                    m_sortList.swapItemsAt(i, j);
                    mi = mj;
                }
                break;
            }
        }
    }
    beginRemoveRows(QModelIndex(), 0, rowCount());
    removeRows(0, rowCount());
    endRemoveRows();
    beginInsertRows(QModelIndex(), 0, rowCount());
    insertRows(0, rowCount());
    endInsertRows();
}

QHash<int, QByteArray> PlaylistListModel::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(ImageListRole::DisplayRole), "display"},
                                         {int(ImageListRole::RatingRole), "rating"},
                                         {int(ImageListRole::FileRole), "file"},
                                         {int(ImageListRole::PathRole), "path"},
                                         {int(ImageListRole::AddedRole), "added"},
                                         {int(ImageListRole::LastPlayRole), "lastPlay"},
                                         {int(ImageListRole::ExtensionRole), "extension"},
                                         {int(ImageListRole::Fullpath), "fullpath"},
                                         {int(ImageListRole::IndexRole), "index"},
                                         {int(ImageListRole::OrderRole), "order"},
                                         {int(ImageListRole::CountRole), "count"}};
    return ret;
}

QStringList PlaylistListModel::columnModel() const {
    QStringList ret;
    for(auto it: m_columns)
        ret<<it.name;

    return ret;
}

QVariant PlaylistListModel::headerData(int section, Qt::Orientation, int) const
{
    return columnModel()[section];
}

void PlaylistListModel::play(int index)
{
    QList<int> read;
    for(auto it = 0; it < m_model->count(); it++)
        read<<it;

    if(m_model->isShuffle())
    {
        QRandomGenerator generator;
        read.swapItemsAt(0, read.indexOf(index));
        for(auto i = 1; i < read.size(); i++) {
            auto r = generator.bounded(i, int(read.count()));
            read.swapItemsAt(i, r);
        }
    }

    m_model->setReadOrder(read);
    m_model->setCurrentIndex(index-1);
    m_model->next();
}

PlaylistListModel::TristateOrder PlaylistListModel::nextOrder(TristateOrder order) {
    switch (order) {
    case TristateOrder::NoOrder:
        return TristateOrder::AscendingOrder;
    case TristateOrder::AscendingOrder:
        return TristateOrder::DescendingOrder;
    case TristateOrder::DescendingOrder:
        return TristateOrder::NoOrder;
    }

    return TristateOrder::NoOrder;
}

bool PlaylistListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(m_columns[index.column()].name == "rating")
        (*m_model)[m_sortList[index.row()]]->setRating(value.toInt());
    emit dataChanged(index, index, {role});
    return true;
}

int PlaylistListModel::columnOf(QString name) const
{
    auto ret = 0;
    for(auto it = 0; it < m_columns.count(); it++) {
        if(m_columns[it].name == name)
            ret = it;
    }

    return ret;
}
