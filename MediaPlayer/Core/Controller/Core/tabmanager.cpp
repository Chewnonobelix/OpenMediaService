#include "tabmanager.h"

void TabManager::setTab(QString id, QQmlComponent *player,
												QQmlComponent *playlist) {
	m_tabs[QUuid::fromString(id)].player = player;
	m_tabs[QUuid::fromString(id)].playlist = playlist;
}

QQmlComponent *TabManager::player(QString id) const {
	return m_tabs[QUuid::fromString(id)].player;
}

QQmlComponent *TabManager::playlist(QString id) const {
	return m_tabs[QUuid::fromString(id)].playlist;
}

QVariant TabManager::data(const QModelIndex &index, int role) const {}
int TabManager::rowCount(const QModelIndex &) const { return m_tabs.size(); }

QHash<int, QByteArray> TabManager::roleNames() const {
	static QHash<int, QByteArray> ret{{int(TabRole::PlaylistRole), "playlist"},
																		{int(TabRole::PlayerRole), "player"}};

	return ret;
}
