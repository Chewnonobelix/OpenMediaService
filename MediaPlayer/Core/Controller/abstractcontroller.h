#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "interfacesaver.h"
#include <QObject>
#include <QQmlApplicationEngine>

class AbstractController : public QObject
{
    Q_OBJECT
public:
    AbstractController() = default;
    AbstractController(const AbstractController &);
    ~AbstractController() = default;

    virtual void exec() = 0;

    static InterfaceSaver *db();
    static void setDb(QString);
signals:

private:
    static InterfaceSaver *m_db;
    static QThread *m_dbThread;
};

#endif // ABSTRACTCONTROLLER_H
