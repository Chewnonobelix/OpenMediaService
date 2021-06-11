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


public:
    TabWrapper() = default;
    ~TabWrapper() = default;

    Q_INVOKABLE QUuid create();
    QPointer<TabManager> get(QUuid);
    Q_INVOKABLE QPointer<TabManager> get(QString);

    void setPlaylist(int, PlaylistPointer);
    void setPlayer(int, QObject*);
    Q_INVOKABLE QUuid currentId() const;
    TabManager *current();

public slots:
    void setCurrentTab(QString);

signals:
    void currentTabChanged();
};

