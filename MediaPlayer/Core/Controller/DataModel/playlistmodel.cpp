#include "playlistmodel.h"

PlaylistModel::PlaylistModel(const PlaylistModel &) : QAbstractListModel() {}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
	if (index.row() >= rowCount() || index.row() < 0)
		return QVariant();

	int i = index.row();

	switch (PlaylistRole(role)) {
	case PlaylistRole::NameRole:
		return i < m_smarts.size() ? m_smarts[i]->name()
															 : m_normals[i - m_smarts.size()]->name();
		break;
	case PlaylistRole::SmartRole:
		return i < m_smarts.size();
		break;

	case PlaylistRole::IdRole:
		return i < m_smarts.size() ? m_smarts[i]->id()
															 : m_normals[i - m_smarts.size()]->id();

		break;
	}

	return QVariant();
}

int PlaylistModel::rowCount(const QModelIndex &) const {
	return m_smarts.size() + m_normals.size();
}

QHash<int, QByteArray> PlaylistModel::roleNames() const {
	static QHash<int, QByteArray> ret{{int(PlaylistRole::NameRole), "name"},
																		{int(PlaylistRole::SmartRole), "smart"},
																		{int(PlaylistRole::IdRole), "id"}};
	return ret;
}

void PlaylistModel::sort(int, Qt::SortOrder) {}

void PlaylistModel::setSmart(QList<SmartPlaylistPointer> s) {
	beginRemoveRows(QModelIndex(), 0, m_smarts.size());
	removeRows(0, m_smarts.size());
	endRemoveRows();

	m_smarts.clear();
	m_smarts = s;

	beginInsertRows(QModelIndex(), 0, m_smarts.size());
	removeRows(0, m_smarts.size());
	endInsertRows();
}

void PlaylistModel::setNormal(QList<PlaylistPointer> n) {
	beginRemoveRows(QModelIndex(), m_smarts.size(), m_normals.size());
	removeRows(m_smarts.size(), m_normals.size());
	endRemoveRows();

	m_normals.clear();
	m_normals = n;

	beginInsertRows(QModelIndex(), m_smarts.size(), m_normals.size());
	removeRows(m_smarts.size(), m_normals.size());
	endInsertRows();
}

int PlaylistModel::currentIndex() const { return m_currentIndex; }
void PlaylistModel::setCurrentIndex(int index) {
	m_currentIndex = index;
	emit currentIndexChanged();
}

PlaylistPointer PlaylistModel::current() const {
	if (m_currentIndex == -1)
		return PlaylistPointer();

	return m_currentIndex < m_smarts.size()
						 ? m_smarts[m_currentIndex]
						 : m_normals[m_currentIndex - m_smarts.size()];
}
