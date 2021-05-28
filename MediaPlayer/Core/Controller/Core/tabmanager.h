#pragma once

#include <QAbstractListModel>
#include <QMap>
#include <QObject>
#include <QQmlComponent>
#include <QUuid>

#include "mediaplayercore_global.h"

#include <Controller/Core/controllerlibrary.h>

class MEDIAPLAYERCORE_EXPORT TabManager : public QAbstractListModel {
	Q_OBJECT
	Q_DISABLE_COPY(TabManager)

    struct Data {
        QUuid id = QUuid::createUuid();
        PlaylistPointer playlist = PlaylistPointer();
        QQmlComponent* player = nullptr;
        void setPlaylist(PlaylistPointer);

    };

    enum class TabRole {LibRole = Qt::UserRole +1, IdRole, PlaylistRole, IsCurrentRole};
    QList<Data> m_model;

public:
	TabManager() = default;
	~TabManager() = default;

    Q_INVOKABLE void addTab();

public:
	QVariant data(const QModelIndex &index, int role) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;

signals:
    void play(Media*);
};
