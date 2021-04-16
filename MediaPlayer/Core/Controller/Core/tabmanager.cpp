#include "tabmanager.h"


void TabManager::addTab()
{
    auto p = QSharedPointer<ControllerLibrary>::create();
    m_tabs[QUuid::fromString(p->id())] = p;
    m_ids<<QUuid::fromString(p->id());
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
    }

}

int TabManager::rowCount(const QModelIndex &) const { return m_tabs.size(); }

QHash<int, QByteArray> TabManager::roleNames() const {
    static QHash<int, QByteArray> ret{{int(TabRole::PlaylistRole), "playlist"},
                                      {int(TabRole::PlayerRole), "player"}};

    return ret;
}
