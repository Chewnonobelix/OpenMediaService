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
        int libIndex = -1;
        int playlistIndex = -1;
    };

    enum class TabRole {LibRole = Qt::UserRole +1, IdRole, PlaylistRole};
    QList<Data> m_model;

public:
	TabManager() = default;
	~TabManager() = default;

    Q_INVOKABLE void addTab();

public:
	QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
};
