#include "tabmanager.h"

void TabManager::addTab()
{
    m_model<<Data{};
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
        return m_model[row].id;
    case TabRole::LibRole:
        return QVariant();
    case TabRole::PlaylistRole:
        return QVariant();
    case TabRole::IsCurrentRole:
        return false;
    }

    return QVariant();
}

int TabManager::rowCount(const QModelIndex &) const { return m_model.size(); }

QHash<int, QByteArray> TabManager::roleNames() const {
    static QHash<int, QByteArray> ret {{int(TabRole::LibRole), "library"},
                                       {int(TabRole::IdRole), "id"},
                                       {int(TabRole::IsCurrentRole), "isCurrentTab"},
                                       {int(TabRole::PlaylistRole), "playlist"}};
    return ret;
}

bool TabManager::removeTab(QUuid)
{
    return false;
}

bool TabManager::moveTab(QUuid, int)
{
    return false;
}

bool TabManager::contains(QUuid) const
{
    return false;
}

TabManager::Data& TabManager::operator[](QUuid)
{
    return m_model.first();
}
