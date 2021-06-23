#include "controllersettings.h"

ControllerSettings::ControllerSettings(LiveQmlEngine& engine): QObject(nullptr), m_engine(engine)
{
    m_settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "Chewnonobelix Inc", "MediaPlayer");
}

void ControllerSettings::display()
{
    m_engine.createWindow(QUrl(QStringLiteral("/Settings.qml")));
}

void ControllerSettings::setPlugin(QString name, bool enable) {
    (*m_settings).setValue("plugin/"+name, enable);
}

bool ControllerSettings::plugin(QString name) const {
    return (*m_settings).value("plugin/"+name, false).toBool();
}

QStringList ControllerSettings::pluginList() const {
    m_settings->beginGroup("plugin");
    auto ret = m_settings->childKeys();
    m_settings->endGroup();
    return ret;
}

void ControllerSettings::setDb(QString name)
{
    m_settings->setValue("Database/name", name);
    emit dbChanged();
}

QString ControllerSettings::db() const
{
    return m_settings->value("Database/name", "DataJson").toString();
}

void ControllerSettings::setValue(QString key, QVariant value)
{
    m_settings->setValue(key, value);
    emit settingsChanged();
}

QVariant ControllerSettings::value(QString key) const
{
    return m_settings->value(key);
}
