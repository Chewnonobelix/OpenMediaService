#include "imagelistmodel.h"

void ImageListModel::setPLaylist(PlaylistPointer p)
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

}

int ImageListModel::rowCount(const QModelIndex&) const
{
    return m_model ? m_model->count() : 0;
}

int ImageListModel::columnCount(const QModelIndex&) const {
    return m_columns.size();
}

QVariant ImageListModel::data(const QModelIndex& index, int) const {
    auto row = index.row(), col = index.column();

    if((row < 0 || row >= rowCount()) || (col < 0 || col >= columnCount()))
        return QVariant();

    auto current = (*m_model)[row];
    auto currentCol = m_columns[col];

    switch(currentCol.second) {
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
    default:
        break;
    }

    return QVariant();
}
void ImageListModel::sort(int , Qt::SortOrder) {}

QHash<int, QByteArray> ImageListModel::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(ImageListRole::DisplayRole), "display"},
                                         {int(ImageListRole::RatingRole), "rating"},
                                         {int(ImageListRole::FileRole), "file"},
                                         {int(ImageListRole::PathRole), "path"},
                                         {int(ImageListRole::AddedRole), "added"},
                                         {int(ImageListRole::LastPlayRole), "lastPlay"},
                                         {int(ImageListRole::ExtensionRole), "extension"},
                                         {int(ImageListRole::CountRole), "count"}};
    return ret;
}

QStringList ImageListModel::columnModel() const {
    QStringList ret;
    for(auto it: m_columns)
        ret<<it.first;

    return ret;
}

QVariant ImageListModel::headerData(int section, Qt::Orientation, int) const
{
    return columnModel()[section];
}
