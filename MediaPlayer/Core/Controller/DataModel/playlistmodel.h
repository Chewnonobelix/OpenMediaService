#pragma once

#include <QAbstractListModel>
#include <QQmlComponent>

#include <Model/library.h>
#include <Model/smartplaylist.h>
#include <Controller/Core/abstractcontroller.h>
#include <Controller/DataModel/smartmodel.h>

class MEDIAPLAYERCORE_EXPORT PlaylistModel : public QAbstractListModel {
	Q_OBJECT
	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY
								 currentIndexChanged)

private:
	enum class PlaylistRole { NameRole = Qt::UserRole + 1, SmartRole, IdRole };
	QList<SmartPlaylistPointer> m_smarts;
	QList<PlaylistPointer> m_normals;
	int m_currentIndex = -1;
    SmartModel m_smartModel;

public:
    PlaylistModel();
	PlaylistModel(const PlaylistModel &);
	~PlaylistModel() = default;

	void setSmart(QList<SmartPlaylistPointer>);
	void setNormal(QList<PlaylistPointer>);

	int currentIndex() const;
	void setCurrentIndex(int);

	PlaylistPointer current() const;
	PlaylistPointer operator[](int) const;

    Q_INVOKABLE void editPlaylist();

public:
	QVariant data(const QModelIndex &index, int role) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	void sort(int, Qt::SortOrder) override;

public slots:
	void onLibraryChanged(LibraryPointer);
    void onPlaylistNameChanged();

signals:
    void currentIndexChanged();
};
