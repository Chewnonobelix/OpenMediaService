#pragma once

#include <QAbstractTableModel>
#include <QMultiMap>
#include <QMutex>
#include <QQueue>
#include <QThread>
#include <QTimer>
#include <QJSEngine>

#include <Model/smartplaylist.h>

class LibrairyImageModel : public QAbstractListModel {
	Q_OBJECT
    Q_DISABLE_COPY(LibrairyImageModel)

	Q_PROPERTY(int size READ size NOTIFY sizeChanged)
    Q_PROPERTY(PlayList* playlist READ playlist)
private:
	enum class ImageRole {
		PathRole = Qt::UserRole + 1,
		CountRole,
		NameRole,
	};

	int m_currentIndex = 0;
	PlaylistPointer m_playlist;
	QQueue<MediaPointer> m_reading;
	QList<QMultiMap<QString, MediaPointer>> m_model;
	QList<int> m_indexes;
	QList<MediaPointer> m_currentDisplay;

    PlayList* playlist() const;
public:
	LibrairyImageModel() = default;
	~LibrairyImageModel() = default;

	void setPlaylist(PlaylistPointer);
	int size() const;
    Q_INVOKABLE QStringList modelAt(int);
	Q_INVOKABLE void setIndexes(int, int);
	Q_INVOKABLE void onDoubleClicked(int);

signals:
	void currentIndexChanged(int, int);
	void sizeChanged();
	void indexesChanged(int, QStringList) const;
	void imageChanged(MediaPointer);

public:
	QVariant data(const QModelIndex &index, int role) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	void sort(int, Qt::SortOrder) override;

public slots:
};
