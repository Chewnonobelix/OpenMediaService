#include "imagemodel.h"

void ImageModel::setPlaylist(PlaylistPointer p) {
	beginRemoveRows(QModelIndex(), 0, rowCount());
	removeRows(0, rowCount());
	endRemoveRows();
	beginRemoveColumns(QModelIndex(), 0, columnCount());
	removeColumns(0, columnCount());
	endRemoveColumns();

	m_playlist = p;

	beginInsertRows(QModelIndex(), 0, rowCount());
	insertRows(0, rowCount());
	endInsertRows();
	beginInsertColumns(QModelIndex(), 0, columnCount());
	insertColumns(0, columnCount());
	endInsertColumns();
}

QVariant ImageModel::data(const QModelIndex &index, int) const {
	if (index.row() >= rowCount() || index.column() >= columnCount() ||
			index.row() < 0 || index.column() < 0)
		return QVariant();

	int row = index.row(), column = index.column();
	switch (column) {
	case 0:
		return (*m_playlist)[row]->paths().first();
	case 1:
		return (*m_playlist)[row]->count();
	}

	return QVariant();
}

int ImageModel::rowCount(const QModelIndex &) const {
	return m_playlist ? m_playlist->count() : 0;
}

int ImageModel::columnCount(const QModelIndex &) const { return 2; }

QHash<int, QByteArray> ImageModel::roleNames() const {
	static QHash<int, QByteArray> ret{{int(ImageRole::CountRole), "count"},
																		{int(ImageRole::PathRole), "path"},
																		{int(ImageRole::DisplayRole), "display"}};

	return ret;
}

void ImageModel::sort(int, Qt::SortOrder) {}

void ImageModel::setCurrentIndex(int i) {
	m_currentIndex = i;
	emit currentIndexChanged(i);
}

int ImageModel::currentIndex() const { return m_currentIndex; }
