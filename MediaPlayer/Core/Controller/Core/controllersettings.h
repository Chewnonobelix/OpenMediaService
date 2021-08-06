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

    Q_INVOKABLE void setPlaylistColumn(QString, QString, bool);
    Q_INVOKABLE bool playlistColumn(QString, QString);

    Q_INVOKABLE void setPlaylistColumnWidth(QString, QString, int);
    Q_INVOKABLE int playlistColumnWidth(QString, QString);

signals:
    void dbChanged();
    void settingsChanged();
};

