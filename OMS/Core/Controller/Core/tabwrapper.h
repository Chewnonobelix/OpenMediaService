#pragma once

#include <QObject>
#include <QMap>
#include <QPointer>
#include <QLoggingCategory>

#include "mediaplayercore_global.h"

#include "tabmanager.h"

class MEDIAPLAYERCORE_EXPORT TabWrapper: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(TabWrapper)

private:
    QMap<QUuid, QPointer<TabManager>> m_model;
    QUuid m_current;


public:
    TabWrapper() = default;
    ~TabWrapper() = default;

    Q_INVOKABLE QUuid create();
    QPointer<TabManager> get(QUuid);
    Q_INVOKABLE QPointer<TabManager> get(QString);
    Q_INVOKABLE bool removeManager(QString);

    void setPlaylist(int);
    void setPlayer(int, QObject*);
    Q_INVOKABLE QUuid currentId() const;
    TabManager *current();

public slots:
    void setCurrentTab(QString);

signals:
    void currentTabChanged();
};

