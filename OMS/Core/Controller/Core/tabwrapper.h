#pragma once

#include <QObject>
#include <QMap>
#include <QPointer>
#include <QLoggingCategory>

#include <liveqmlengine.h>

#include "mediaplayercore_global.h"

#include "tabmanager.h"

class LibraryDataModel;

class MEDIAPLAYERCORE_EXPORT TabWrapper: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(TabWrapper)

private:
    QMap<QUuid, QPointer<TabManager>> m_model;
    QUuid m_current;
    LiveQmlEngine& m_engine;
    QMap<QUuid, QPointer<LibraryDataModel>> m_libraries;

public:
    TabWrapper(LiveQmlEngine&);
    ~TabWrapper() = default;

    Q_INVOKABLE QUuid create();
    Q_INVOKABLE void createWindow();
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
    void sCreateWindow();
};

