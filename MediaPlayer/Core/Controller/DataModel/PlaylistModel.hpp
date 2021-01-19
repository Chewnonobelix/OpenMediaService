#pragma once

#include <QAbstractListModel>

#include <Model/smartplaylist.h>

#include <Controller/Core/abstractcontroller.h>

class PlaylistModel : public QAbstractListModel {
	Q_OBJECT
	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY
								 currentIndexChanged)

private:
	enum class PlaylistRole { NameRole = Qt::UserRole + 1, SmartRole, IdRole };
	QList<SmartPlaylistPointer> m_smarts;
	QList<PlaylistPointer> m_normals;
	int m_currentIndex = -1;

public:
	PlaylistModel() = default;
	PlaylistModel(const PlaylistModel &);
	~PlaylistModel() = default;

	void setSmart(QList<SmartPlaylistPointer>);
	void setNormal(QList<PlaylistPointer>);

	int currentIndex() const;
	void setCurrentIndex(int);

	PlaylistPointer current() const;

public:
	QVariant data(const QModelIndex &index, int role) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	void sort(int, Qt::SortOrder) override;

signals:
	void currentIndexChanged();
};
