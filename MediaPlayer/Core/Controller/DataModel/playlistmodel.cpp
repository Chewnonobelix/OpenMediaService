#include "playlistmodel.h"
#include <Controller/Core/controllerlibrary.h>

PlaylistModel::PlaylistModel(const PlaylistModel &) : QAbstractListModel() {}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
	if (index.row() >= rowCount() || index.row() < 0)
		return QVariant();

	int i = index.row();

	auto p = (*this)[i];
	switch (PlaylistRole(role)) {
	case PlaylistRole::NameRole:
		return p->name();
		break;
	case PlaylistRole::SmartRole:
		return i < m_smarts.size();
		break;

	case PlaylistRole::IdRole:
		return p->id();

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
	beginRemoveRows(QModelIndex(), 0, m_smarts.size() - 1);
	removeRows(0, m_smarts.size() - 1);
	endRemoveRows();

	m_smarts.clear();
	m_smarts = s;

	beginInsertRows(QModelIndex(), 0, m_smarts.size() - 1);
	insertRows(0, m_smarts.size() - 1);
	endInsertRows();
}

void PlaylistModel::setNormal(QList<PlaylistPointer> n) {
	beginRemoveRows(QModelIndex(), m_smarts.size() - 1, m_normals.size() - 1);
	removeRows(m_smarts.size() - 1, m_normals.size() - 1);
	endRemoveRows();

	m_normals.clear();
	m_normals = n;

	beginInsertRows(QModelIndex(), m_smarts.size() - 1, m_normals.size() - 1);
	insertRows(m_smarts.size() - 1, m_normals.size() - 1);
	endInsertRows();
}

int PlaylistModel::currentIndex() const { return m_currentIndex; }

void PlaylistModel::setCurrentIndex(int index) {
	m_currentIndex = index;
	emit currentIndexChanged(current());

	//	auto cl = ControllerLibrary::active();
	//	auto plug = cl->plugins();

	//	if (plug)
	//		plug->setPlaylist((*this)[index < 0 ? 0 : index]);
}

PlaylistPointer PlaylistModel::current() const {
	if (m_currentIndex == -1)
		return PlaylistPointer();

	return m_currentIndex < m_smarts.size()
						 ? m_smarts[m_currentIndex]
						 : m_normals[m_currentIndex - m_smarts.size()];
}

void PlaylistModel::onLibraryChanged(LibraryPointer l) {
	qDebug() << "Connard" << l;
	if (l.isNull())
		return;

	setSmart(l->smartPlaylist().values());
	setNormal(l->playlist().values());

	//	auto view = ControllerLibrary::active()->plugins()->playlistView();
	//	emit displayChanged(view);
}

PlaylistPointer PlaylistModel::operator[](int index) const {
	return index < m_smarts.size() ? m_smarts[index]
																 : m_normals[index - m_smarts.size()];
}
