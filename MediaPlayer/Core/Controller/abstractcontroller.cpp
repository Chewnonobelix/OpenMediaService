#include "abstractcontroller.h"

InterfaceSaver *AbstractController::m_db = nullptr;
QThread *AbstractController::m_dbThread = new QThread();

AbstractController::AbstractController(const AbstractController &) : QObject() {}

InterfaceSaver *AbstractController::db()
{
    return m_db;
}

void AbstractController::setDb(QString name)
{
    int type = QMetaType::type(name.toLatin1());
    if (type == QMetaType::UnknownType)
        throw QString("Unknow DB type");

    if (m_db != nullptr) {
        m_db->thread()->terminate();
        m_db->thread()->wait();

        delete m_db;
    }
    m_dbThread->start();

    m_db = (InterfaceSaver *) (QMetaType::create(type));
    m_db->init();
    m_db->moveToThread(m_dbThread);
}
