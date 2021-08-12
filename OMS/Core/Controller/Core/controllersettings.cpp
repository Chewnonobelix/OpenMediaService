#include "controllersettings.h"

ControllerSettings::ControllerSettings(LiveQmlEngine& engine): QObject(nullptr), m_engine(engine)
{
    m_settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "Chewnonobelix Inc", "OpenMediaService");

    m_language.load(language());
}

void ControllerSettings::display()
{
    auto context = new QQmlContext(m_engine.qmlEngine().rootContext());
    context->setContextProperty("_language", &m_language);

    m_engine.createWindow(QUrl(QStringLiteral("/Settings.qml")), context);
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

void ControllerSettings::setPlaylistColumn(QString plId, QString column, bool enable)
{
    m_settings->setValue(plId + "/" + column, enable);
}

bool ControllerSettings::playlistColumn(QString plId, QString column)
{
    return m_settings->value(plId + "/" + column, true).toBool();
}

void ControllerSettings::setPlaylistColumnWidth(QString plId, QString column, int width)
{
    m_settings->setValue(plId + "/" + column + "Width", width);
}

int ControllerSettings::playlistColumnWidth(QString plId, QString column)
{
    return m_settings->value(plId + "/" + column + "Width", -1).toInt();
}

void ControllerSettings::setLanguage(QString lang)
{
    if(m_language.load(lang)) {
        m_settings->setValue("language", lang);
        m_engine.qmlEngine().retranslate();
    }
}

QString ControllerSettings::language() const
{
    return m_settings->value("language").toString();
}
