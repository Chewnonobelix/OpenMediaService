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
