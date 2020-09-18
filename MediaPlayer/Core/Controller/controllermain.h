#ifndef CONTROLLERMAIN_H
#define CONTROLLERMAIN_H

#include "DataXml.h"
#include "abstractcontroller.h"
#include "liveqmlengine.h"
#include <QCoreApplication>
#include <QObject>
#include <QQmlContext>
class ControllerMain : public AbstractController
{
    Q_OBJECT
    Q_DISABLE_COPY(ControllerMain)
private:
    LiveQmlEngine m_engine;

    QQmlApplicationEngine &engine();

public:
    ControllerMain();
    ~ControllerMain() = default;

    void exec();

public slots:
    void onAddLibrary(LibraryPointer = LibraryPointer());

signals:
    void libraryModelChanged(QList<Library *>);
};


#endif // CONTROLLERMAIN_H
