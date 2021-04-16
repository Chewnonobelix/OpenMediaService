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

	struct Tab {
		Q_GADGET

	public:
		QQmlComponent *player;
		QQmlComponent *playlist;
	};

	enum class TabRole { PlayerRole = Qt::UserRole + 1, PlaylistRole };
    QMap<QUuid, QSharedPointer<ControllerLibrary>> m_tabs;
    QList<QUuid> m_ids;

public:
	TabManager() = default;
	~TabManager() = default;

    Q_INVOKABLE void addTab();
	void setTab(QString, QQmlComponent *, QQmlComponent *);
	Q_INVOKABLE QQmlComponent *player(QString) const;
	Q_INVOKABLE QQmlComponent *playlist(QString) const;

public:
	QVariant data(const QModelIndex &index, int role) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
};
