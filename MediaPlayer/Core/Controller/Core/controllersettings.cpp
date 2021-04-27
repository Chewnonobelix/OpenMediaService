#include "controllersettings.h"

void ControllerSettings::exec()
{
    auto context = m_engine->qmlEngine().rootContext();
    context->setContextProperty("_settings", this);

    m_settings = new QSettings(QSettings::UserScope, "Chewnonobelix Inc.", "MediaPlayer");

}

void ControllerSettings::display()
{
    m_engine->createWindow(QUrl(QStringLiteral("/Settings.qml")));
}
