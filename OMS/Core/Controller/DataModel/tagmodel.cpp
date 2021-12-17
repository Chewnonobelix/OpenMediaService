#include "tagmodel.h"

TagModel::TagModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int TagModel::rowCount(const QModelIndex &) const
{
    return m_model.count();
}

QVariant TagModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(TagRole(role)) {
    case TagRole::TagRole:
        return m_model[index.row()].second;
        break;
    case TagRole::UidRole:
        return m_model[index.row()].first;
        break;
    }

    // FIXME: Implement me!
    return QVariant();
}

QHash<int, QByteArray> TagModel::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(TagRole::TagRole), "tag"},
                                         {int(TagRole::UidRole), "uid"}};

    return ret;
}

bool TagModel::addTag(QString tag)
{
    auto find = std::find_if(m_model.begin(), m_model.end(), [tag](auto it) {
                    return tag == it.second;
                }) != m_model.end();

    if(!find) {
        auto newTag = QPair<QUuid, QString>{QUuid::createUuid(), tag};
        emit s_addTag(newTag);
        return true;
    }

    return false;
}

bool TagModel::editTag(QUuid id, QString tag)
{
    auto ret = std::find_if(m_model.begin(), m_model.end(), [id](auto it) {
        return id == it.first;
    });

    if(ret != m_model.end()) {
        (*ret).second = tag;
        emit s_editTag(*ret);

        beginResetModel();
        endResetModel();
        return true;
    }

    return false;
}

bool TagModel::removeTag(QUuid id)
{
    auto ret = std::find_if(m_model.begin(), m_model.end(), [id](auto it) {
        return id == it.first;
    });

    if(ret != m_model.end()) {
        emit s_removeTag(*ret);
        return true;
    }

    return false;
}

void TagModel::setModel(QList<MediaPlayerGlobal::Tag> model)
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    endRemoveRows();

    m_model = model;

    beginInsertRows(QModelIndex(), 0, rowCount() - 1);
    endInsertRows();
}
