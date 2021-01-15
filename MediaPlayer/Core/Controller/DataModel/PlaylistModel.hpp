#pragma once

#include <QAbstractListModel>

#include <Model/smartplaylist.h>

class PlaylistModel : public QAbstractListModel {
private:
	enum class PlaylistRole { NameRole = Qt::UserRole + 1, SmartRole };
	QList<SmartPlaylistPointer> m_smarts;
	QList<PlaylistPointer> m_normals;

public:
	PlaylistModel() = default;
	PlaylistModel(const PlaylistModel &);
	~PlaylistModel() = default;

	void setSmart(QList<SmartPlaylistPointer>);
	void setNormal(QList<PlaylistPointer>);

public:
	QVariant data(const QModelIndex &index, int role) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	void sort(int, Qt::SortOrder) override;
};
