#pragma once

#include <QAbstractTableModel>
#include <QQueue>

#include <Model/smartplaylist.h>

class ImageModel : public QAbstractTableModel {
	Q_OBJECT

	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY
								 currentIndexChanged)

private:
	enum class ImageRole { PathRole = Qt::UserRole + 1, CountRole, DisplayRole };

	PlaylistPointer m_playlist;

	QQueue<MediaPointer> m_reading;

	int m_currentIndex = -1;

public:
	ImageModel() = default;
	ImageModel(const ImageModel &);
	~ImageModel() = default;

	void setPlaylist(PlaylistPointer);
	int currentIndex() const;
	void setCurrentIndex(int);

signals:
	void currentIndexChanged(int);

public:
	QVariant data(const QModelIndex &index, int role) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	void sort(int, Qt::SortOrder) override;
};
