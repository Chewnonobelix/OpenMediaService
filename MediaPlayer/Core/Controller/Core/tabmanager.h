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
    };

    enum class TabRole {LibRole = Qt::UserRole +1, IdRole, PlaylistRole, IsCurrentRole};
    QList<Data> m_model;

    QUuid m_id = QUuid::createUuid();

public:
	TabManager() = default;
	~TabManager() = default;

    QUuid id() const;

    Q_INVOKABLE void addTab();
    Q_INVOKABLE bool removeTab(QUuid);
    Q_INVOKABLE bool moveTab(QUuid, int);

    bool contains(QUuid) const;
    Data& operator[](QUuid);

public:
	QVariant data(const QModelIndex &index, int role) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;

signals:
    void clicked(QUuid);
};
