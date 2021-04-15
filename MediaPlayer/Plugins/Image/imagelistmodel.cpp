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
    return 6;
}

QVariant ImageListModel::data(const QModelIndex& index, int) const {
    auto row = index.row(), col = index.column();

    if((row < 0 || row >= rowCount()) || (col < 0 || col >= columnCount()))
        return QVariant();

    auto current = (*m_model)[row];
    qDebug()<<row<<col<<current->path();
    switch(col) {
    case 0:
        return current->path().split("/").last();
        break;
    case 1: {
        auto last = current->path().lastIndexOf("/");
        return current->path().mid(0, last);
    }
        break;
    case 2:
        return current->count();
        break;
    case 3:
        return current->added();
        break;
    case 4:
        return current->lastFinish();
        break;
    case 5: {
        auto last = current->path().lastIndexOf(".");
        return current->path().mid(last);
    }
        break;
    }

    return QVariant();
}
void ImageListModel::sort(int , Qt::SortOrder) {}

QHash<int, QByteArray> ImageListModel::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(ImageListRole::DisplayRole), "display"}};
    return ret;
}
