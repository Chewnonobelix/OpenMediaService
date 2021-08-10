#pragma once

#include <QAbstractListModel>
#include <QMap>
#include <QObject>
#include <QQmlComponent>
#include <QUuid>
#include <QPointer>

#include "mediaplayercore_global.h"

#include <Model/playlist.h>

class MEDIAPLAYERCORE_EXPORT TabManager : public QAbstractListModel {
	Q_OBJECT
	Q_DISABLE_COPY(TabManager)

    struct Data {
        QUuid id = QUuid::createUuid();
        QObject* player = nullptr;

        int playlistIndex = -1;
        int libIndex = -1;
    };

    QList<Data> m_model;

    QUuid m_id = QUuid::createUuid();

public:
    enum class TabRole {PlayerRole = Qt::UserRole +1, IdRole, DataRole, LibraryIndex, PLaylistIndex};

    TabManager() = default;
	~TabManager() = default;

    QUuid id() const;

    Q_INVOKABLE void addTab();
    Q_INVOKABLE bool removeTab(QUuid);
    Q_INVOKABLE bool moveTab(QUuid, int);

    bool contains(QUuid) const;
    Data& operator[](QUuid);

    int indexOf(QUuid) const;
public:
	QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &, int = Qt::EditRole) override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;

signals:
    void clicked(QString);
};
