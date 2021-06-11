#pragma once

#include <QSettings>

#include <liveqmlengine.h>

#include "mediaplayercore_global.h"

class MEDIAPLAYERCORE_EXPORT ControllerSettings: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ControllerSettings)

private:
    QPointer<QSettings> m_settings;
    LiveQmlEngine& m_engine;

public:
    ControllerSettings(LiveQmlEngine&);
    ~ControllerSettings() = default;

    void exec();

    Q_INVOKABLE void display();

    Q_INVOKABLE void setPlugin(QString, bool);
    bool plugin(QString) const;
    QStringList pluginList() const;

    Q_INVOKABLE void setDb(QString);
    Q_INVOKABLE QString db() const;

    Q_INVOKABLE void setValue(QString, QVariant);
    Q_INVOKABLE QVariant value(QString) const;

signals:
    void dbChanged();
};

