#include "tabmanager.h"

QUuid TabManager::s_currentTab = QUuid();

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
        return m_model[row].libIndex;
    case TabRole::PlaylistRole:
        return m_model[row].playlistIndex;
    case TabRole::IsCurrentRole:
        return m_model[row].id == s_currentTab;
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

bool TabManager::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto erole = TabRole(role);

    switch(erole)
    {
    case TabRole::LibRole:
        m_model[index.row()].libIndex = value.toInt();
        break;
    case TabRole::PlaylistRole:
        m_model[index.row()].playlistIndex = value.toInt();
        break;
    default:
        break;
    }

    return true;
}

void TabManager::setCurrentTab(QString id)
{
    s_currentTab = QUuid::fromString(id);
}

QUuid TabManager::currentTab()
{
    return s_currentTab;
}
