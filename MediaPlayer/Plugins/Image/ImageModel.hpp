#pragma once

#include <QAbstractTableModel>
#include <QQueue>

#include <Model/smartplaylist.h>

class ImageModel : public QAbstractTableModel {
	Q_OBJECT

private:
	enum class ImageRole { PathRole = Qt::UserRole + 1, CountRole };

	PlaylistPointer m_playlist;

	QQueue<MediaPointer> m_reading;

public:
	ImageModel() = default;
	ImageModel(const ImageModel &);
	~ImageModel() = default;

	void setPlaylist(PlaylistPointer);

public:
	QVariant data(const QModelIndex &index, int role) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	void sort(int, Qt::SortOrder) override;
};
