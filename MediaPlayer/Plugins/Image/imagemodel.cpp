#include "imagemodel.h"

void ImageModel::setPlaylist(PlaylistPointer p) {
	beginRemoveRows(QModelIndex(), 0, rowCount());
	removeRows(0, rowCount());
	endRemoveRows();

	m_playlist = p;

	beginInsertRows(QModelIndex(), 0, rowCount());
	insertRows(0, rowCount());
	endInsertRows();

	m_model.clear();
	QTime timer = QTime::currentTime();
	for (auto it = 0; it < p->count(); it++) {
		auto path = (*p)[it]->path();
		auto list = path.split('/');
		if (m_model.size() < list.size() - 1)
			m_model.resize(list.size() - 1, {{"All", {"*"}}});

		for (auto it2 = 0; it2 < list.size() - 1; it2++) {
			m_model[it2].insert(list[it2], path);
		}
	}

	qDebug() << "Elapsed" << timer.msecsTo(QTime::currentTime()) << p->count();
	m_indexes.resize(m_model.size(), 0);

	emit sizeChanged();

	for (auto it = 0; it < m_model.size(); it++) {
		setIndexes(it, m_model[it].uniqueKeys().indexOf("All"));
	}

	for (auto it = 0; it < m_indexes.size(); it++)
		emit currentIndexChanged(it, m_indexes[it]);
}

QVariant ImageModel::data(const QModelIndex &index, int) const {
	if (index.row() >= rowCount() || index.row() < 0)
		return QVariant();

	return QVariant();
}

int ImageModel::rowCount(const QModelIndex &) const {
	return m_playlist ? m_playlist->count() : 0;
}

QHash<int, QByteArray> ImageModel::roleNames() const {
	static QHash<int, QByteArray> ret{{int(ImageRole::CountRole), "count"},
																		{int(ImageRole::PathRole), "path"},
																		{int(ImageRole::DisplayRole), "display"}};

	return ret;
}

void ImageModel::sort(int, Qt::SortOrder) {}

int ImageModel::size() const { return m_model.size(); }

void ImageModel::modelAt(int index) {
	auto m = m_model[index].uniqueKeys();

	emit indexesChanged(index, m);
}

void ImageModel::setIndexes(int t, int i) {
	m_indexes[t] = i;

	for (auto it = t + 1; it < m_model.size(); it++)
		modelAt(it);
}
