#include "abstractcontroller.h"

InterfaceSaver *AbstractController::s_db = nullptr;
QThread *AbstractController::s_dbThread = new QThread();
QPointer<LiveQmlEngine> AbstractController::s_engine = nullptr;
PluginManager AbstractController::s_manager = PluginManager();
QPointer<ControllerSettings> AbstractController::s_settings = nullptr;
QPointer<TabWrapper> AbstractController::s_tabWrapper = new TabWrapper;

AbstractController::AbstractController() : QObject() {
    if(s_engine.isNull()) {
        s_engine = new LiveQmlEngine(nullptr, QStringLiteral(QML_SOURCE) + "/View");
    }

    if (s_settings.isNull()) {
        s_settings = new ControllerSettings(*s_engine);
    }
}

InterfaceSaver *AbstractController::db() { return s_db; }

void AbstractController::setDb(QString name) {
	auto type = QMetaType::fromName(name.toLatin1());

    if (s_db != nullptr) {
        s_db->thread()->terminate();
        s_db->thread()->wait();

        delete s_db;
	}

    if (!type.isValid())
        throw QString("Unknow DB type");

    s_dbThread->start();

    s_db = (InterfaceSaver *)(type.create());
    s_db->init();
    s_db->moveToThread(s_dbThread);

    emit s_db->librariesChanged();
}

QPointer<LiveQmlEngine>& AbstractController::engine()
{
    return s_engine;
}
