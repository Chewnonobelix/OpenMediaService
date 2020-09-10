#include "controllermain.h"

ControllerMain::ControllerMain()
    : AbstractController(), m_engine(this, QStringLiteral(QML_SOURCE) + "/View")
{}

void ControllerMain::exec()
{
    auto *context = engine().rootContext();
    context->setContextProperty("_main", this);

    m_engine.createWindow(QUrl("/Main.qml"));
}

QQmlApplicationEngine &ControllerMain::engine()
{
    return m_engine.qmlEngine();
}
