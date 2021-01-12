#include "abstractcontroller.h"

InterfaceSaver *AbstractController::m_db = nullptr;
QThread *AbstractController::m_dbThread = new QThread();
QPointer<LiveQmlEngine> AbstractController::m_engine = nullptr;

AbstractController::AbstractController() : QObject() {
	if (m_engine.isNull())
		m_engine = new LiveQmlEngine(nullptr, QStringLiteral(QML_SOURCE) + "/View");
}

AbstractController::AbstractController(const AbstractController &) : QObject() {
	if (m_engine.isNull())
		m_engine = new LiveQmlEngine(nullptr, QStringLiteral(QML_SOURCE) + "/View");
}

InterfaceSaver *AbstractController::db() { return m_db; }

void AbstractController::setDb(QString name) {
	auto type = QMetaType::fromName(name.toLatin1());
	if (!type.isValid())
		throw QString("Unknow DB type");

	if (m_db != nullptr) {
		m_db->thread()->terminate();
		m_db->thread()->wait();

		delete m_db;
	}
	m_dbThread->start();

	m_db = (InterfaceSaver *)(type.create());
	m_db->init();
	m_db->moveToThread(m_dbThread);
}
