#include "controllermain.h"

ControllerMain::ControllerMain(const ControllerMain &) : AbstractController() {}

void ControllerMain::exec()
{
    auto *context = engine().rootContext();
    context->setContextProperty("_main", this);

    engine().load(QUrl("qrc:/Main.qml"));

    auto *root = engine().rootObjects().first();
    QMetaObject::invokeMethod(root, "show");
}

QQmlApplicationEngine &ControllerMain::engine()
{
    return m_engine;
}
