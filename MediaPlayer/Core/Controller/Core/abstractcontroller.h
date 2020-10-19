#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "..\Data\interfacesaver.h"
#include <QObject>
#include <liveqmlengine.h>

class AbstractController : public QObject
{
    Q_OBJECT
public:
    AbstractController();
    AbstractController(const AbstractController &);
    ~AbstractController() = default;

    virtual void exec() = 0;

    static InterfaceSaver *db();
    static void setDb(QString);
signals:

protected:
    static QPointer<LiveQmlEngine> m_engine;

private:
    static InterfaceSaver *m_db;
    static QThread *m_dbThread;
};

#endif // ABSTRACTCONTROLLER_H
