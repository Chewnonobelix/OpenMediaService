#include "tabmanager.h"


void TabManager::addTab()
{
    auto p = QSharedPointer<ControllerLibrary>::create();
    p->exec();
    m_tabs[QUuid::fromString(p->id())] = p;
    m_ids<<QUuid::fromString(p->id());

    beginInsertRows(QModelIndex(), rowCount() - 1, rowCount()-1);
    insertRows(rowCount()- 1, 1);
    endInsertRows();
}

QQmlComponent *TabManager::player(QString id) const {
    return m_tabs[QUuid::fromString(id)]->playerComponent();
}

QQmlComponent *TabManager::playlist(QString id) const {
    return m_tabs[QUuid::fromString(id)]->playlistComponent();
}

QVariant TabManager::data(const QModelIndex &index, int role) const {
    auto row = index.row();
    if(row < 0 || row >= rowCount())
        return QVariant();

    auto roleEnum = TabRole(role);
    auto id = m_ids[row];

    switch(roleEnum) {
    case TabRole::PlayerRole:
        return QVariant::fromValue(player(id.toString()));
    case TabRole::PlaylistRole:
        return QVariant::fromValue(playlist(id.toString()));
    case TabRole::ModelRole:
        return QVariant::fromValue(m_tabs[id].data());
    }

}

ControllerLibrary* TabManager::at(int index) const {
    return index >= 0 && index < rowCount() ? m_tabs[m_ids[index]].data() : nullptr;
}

int TabManager::rowCount(const QModelIndex &) const { return m_tabs.size(); }

QHash<int, QByteArray> TabManager::roleNames() const {
    static QHash<int, QByteArray> ret{{int(TabRole::PlaylistRole), "playlist"},
                                      {int(TabRole::PlayerRole), "player"},
                                      {int(TabRole::ModelRole), "model"}};

    return ret;
}
