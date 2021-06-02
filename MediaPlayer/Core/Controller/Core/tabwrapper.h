#pragma once

#include <QObject>
#include <QMap>
#include <QPointer>

#include "mediaplayercore_global.h"

#include "tabmanager.h"

class MEDIAPLAYERCORE_EXPORT TabWrapper: public QObject
{
    Q_OBJECT

private:
    QMap<QUuid, QPointer<TabManager>> m_model;
    QUuid m_current;

    QPointer<TabManager>& current();

public:
    TabWrapper() = default;
    ~TabWrapper() = default;

    Q_INVOKABLE QUuid create();
    QPointer<TabManager> get(QUuid);
    Q_INVOKABLE QPointer<TabManager> get(QString);

    void setPlaylist(PlaylistPointer);
    void setPlayer(QQmlComponent*);
    QUuid currentId() const;

public slots:
    void setCurrentTab(QString);
};

