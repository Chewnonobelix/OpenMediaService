#pragma once

#include <QObject>
#include <QMap>

#include "tabmanager.h"

class TabWrapper: public QObject
{
    Q_OBJECT

private:
    QMap<QUuid, QPointer<TabManager>> m_model;
    QUuid m_current;

    Q_INVOKABLE QUuid create();
    Q_INVOKABLE QPointer<TabManager> get(QUuid);

public:
    TabWrapper() = default;
    ~TabWrapper() = default;
};

