#include "librairyimagemodel.h"

void LibrairyImageModel::setPlaylist(PlaylistPointer p) {
	m_playlist = p;
	m_model.clear();

	for (auto it = 0; it < p->count(); it++) {
		auto path = (*p)[it]->path();
		auto list = path.split('/');
		if (m_model.size() < list.size())
			m_model.resize(list.size(), {{"All", {}}});

		for (auto it2 = 0; it2 < list.size() - 1; it2++) {
			m_model[it2].insert(list[it2], (*p)[it]);
			m_model[it2].insert("All", (*p)[it]);
		}
	}

	m_indexes.resize(m_model.size(), 0);

	emit sizeChanged();

	modelAt(0);
	for (auto it = 0; it < m_model.size(); it++) {
		setIndexes(it, m_model[it].uniqueKeys().indexOf("All"));
	}

	for (auto it = 0; it < m_indexes.size(); it++)
		emit currentIndexChanged(it, m_indexes[it]);
}

QVariant LibrairyImageModel::data(const QModelIndex &index, int type) const {
	if (index.row() >= rowCount() || index.row() < 0)
		return QVariant();

	ImageRole role = ImageRole(type);
	int row = index.row();

	switch (role) {
	case ImageRole::CountRole:
		return m_currentDisplay[row]->count();
	case ImageRole::NameRole:
		return m_currentDisplay[row]->path().split("/").last();
	case ImageRole::PathRole:
		return m_currentDisplay[row]->path();
	}

	return QVariant();
}

int LibrairyImageModel::rowCount(const QModelIndex &) const {
	return m_currentDisplay.count();
}

QHash<int, QByteArray> LibrairyImageModel::roleNames() const {
	static QHash<int, QByteArray> ret{{int(ImageRole::CountRole), "count"},
																		{int(ImageRole::PathRole), "path"},
																		{int(ImageRole::NameRole), "name"}};

	return ret;
}

void LibrairyImageModel::sort(int, Qt::SortOrder) {}

int LibrairyImageModel::size() const { return m_model.size() - 1; }

void LibrairyImageModel::modelAt(int index) {

	QStringList ret;
	if (index == 0)
		ret = m_model[0].uniqueKeys();
	else {
		// ret = m_model[index].uniqueKeys();
		auto ti = m_indexes[index - 1];
		auto vals =
				ti >= 0 ? m_model[index - 1].values(m_model[index - 1].uniqueKeys()[ti])
								: QList<MediaPointer>();

		QMultiMap<QString, MediaPointer> temp;
		for (auto it : vals) {
			if (it.isNull())
				continue;

			auto split = it->path().split("/");
			if (index < split.size() - 1) {
				temp.insert(split[index], it);
				temp.insert("All", it);
			}
		}

		ret = temp.uniqueKeys();
	}

	emit indexesChanged(index, ret);
	emit currentIndexChanged(index, ret.indexOf("All"));
}

void LibrairyImageModel::setIndexes(int t, int i) {

	m_indexes[t] = i;

	for (auto it = t + 1; it < m_model.size(); it++) {
		modelAt(it);
	}

	beginRemoveRows(QModelIndex(), 0, rowCount());
	removeRows(0, rowCount());
	endRemoveRows();

	m_currentDisplay.clear();
	for (auto it = 0; it < m_model.size(); it++) {
		if (m_indexes[it] < 0)
			continue;

		auto vals = m_model[it].values(m_model[it].uniqueKeys()[m_indexes[it]]);
		for (auto it2 : vals) {
			if (it2.isNull())
				continue;

			auto split = it2->path().split("/");
			if (split.count() - 2 == it && m_currentDisplay.count(it2) == 0) {
				m_currentDisplay << it2;
			}
		}
	}

	beginInsertRows(QModelIndex(), 0, rowCount() - 1);
	insertRows(0, rowCount() - 1);
	endInsertRows();
}

void LibrairyImageModel::onDoubleClicked(int i) {
	QList<int> read;
	for (auto it = i; it < m_currentDisplay.count(); it++)
		read << (m_playlist->indexOf(m_currentDisplay[it]));

	m_playlist->setReadOrder(read);
	m_playlist->next();
}
