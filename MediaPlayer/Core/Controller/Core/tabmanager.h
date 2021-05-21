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

    enum class TabRole {LibRole = Qt::UserRole +1, IdRole, PlaylistRole, IsCurrentRole};
    QList<Data> m_model;

    static QUuid s_currentTab;
    static QList<Data>::iterator s_current;
    static QList<TabManager*> s_list;

public:
	TabManager() = default;
	~TabManager() = default;

    Q_INVOKABLE void addTab();
    Q_INVOKABLE void setCurrentTab(QString);
    static QUuid currentTabId();
    static void setGlobalCurrentPlaylist(int);
    static void setGlobalCurrentLibrary(int);

    void setCurrentPlaylist(int);
    void setCurrentLibrary(int);

    Q_INVOKABLE QVariant at(int, QString) const;

public:
	QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
};
