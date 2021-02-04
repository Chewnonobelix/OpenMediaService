#pragma once

#include <QAbstractTableModel>
#include <QMultiMap>
#include <QMutex>
#include <QQueue>
#include <QThread>

#include <Model/smartplaylist.h>

class ImageModel : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(int size READ size NOTIFY sizeChanged)

private:
	enum class ImageRole { PathRole = Qt::UserRole + 1, CountRole, DisplayRole };

	PlaylistPointer m_playlist;

	QQueue<MediaPointer> m_reading;

	QList<QMultiMap<QString, QString>> m_model;

	QList<int> m_indexes;

public:
	ImageModel() = default;
	ImageModel(const ImageModel &);
	~ImageModel() = default;

	void setPlaylist(PlaylistPointer);
	int size() const;
	Q_INVOKABLE void modelAt(int);
	Q_INVOKABLE void setIndexes(int, int);

signals:
	void currentIndexChanged(int, int);
	void sizeChanged();
	void indexesChanged(int, QStringList) const;

public:
	QVariant data(const QModelIndex &index, int role) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	void sort(int, Qt::SortOrder) override;
};
