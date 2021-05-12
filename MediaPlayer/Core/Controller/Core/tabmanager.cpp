#include "tabmanager.h"


void TabManager::addTab()
{
    m_model<<QPair<QUuid, int>{QUuid::createUuid(), -1};
    beginInsertRows(QModelIndex(), rowCount() - 1, rowCount()-1);
    insertRows(rowCount()- 1, 1);
    endInsertRows();
}

QVariant TabManager::data(const QModelIndex &index, int role) const {
    auto row = index.row();
    if(row < 0 || row >= rowCount())
        return QVariant();

    auto roleEnum = TabRole(role);

    switch(roleEnum)
    {
    case TabRole::IdRole:
        return m_model[row].first;
    case TabRole::IndexRole:
        return m_model[row].second;
    }

    return QVariant();
}

int TabManager::rowCount(const QModelIndex &) const { return m_model.size(); }

QHash<int, QByteArray> TabManager::roleNames() const {
    static QHash<int, QByteArray> ret {{int(TabRole::IndexRole), "index"},
                                       {int(TabRole::IdRole), "id"}};
    return ret;
}

bool TabManager::setData(const QModelIndex &index, const QVariant &value, int)
{
    qDebug()<<index<<value;
    m_model[index.row()].second = value.toInt();

    return true;
}

