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

	for (auto it = 0; it < p->count(); it++) {
		auto path = (*p)[it]->path();
		auto list = path.split('/');
		if (m_model.size() < list.size())
			m_model.resize(list.size(), {{"All", {}}});

		for (auto it2 = 0; it2 < list.size() - 1; it2++) {
			m_model[it2].insert(list[it2], path);
			m_model[it2].insert("All", path);
		}
	}

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

	QStringList ret;
	if (index == 0)
		ret = m_model[0].uniqueKeys();
	else {
		// ret = m_model[index].uniqueKeys();
		auto ti = m_indexes[index - 1];
		auto vals =
				ti >= 0 ? m_model[index - 1].values(m_model[index - 1].uniqueKeys()[ti])
								: QStringList();

		QMultiMap<QString, QString> temp;
		for (auto it : vals) {
			auto split = it.split("/");
			if (index < split.size() - 1) {
				temp.insert(split[index], it);
				temp.insert("All", it);
			}
		}

		ret = temp.uniqueKeys();
	}

	emit indexesChanged(index, ret);
}

void ImageModel::setIndexes(int t, int i) {

	m_indexes[t] = i;

	for (auto it = t; it < m_model.size(); it++)
		modelAt(it);
}
