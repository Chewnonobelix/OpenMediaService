#include "tagmodel.h"

TagModel::TagModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int TagModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant TagModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

QHash<int, QByteArray> TagModel::roleNames() const
{
    static QHash<int, QByteArray> ret = {};

    return ret;
}

bool TagModel::addTag(Qstring)
{
    return false;
}

bool TagModel::editTag(QUuid, QString)
{
    return false;
}

bool TagModel::removeTag(QUuid)
{
    return false;
}
