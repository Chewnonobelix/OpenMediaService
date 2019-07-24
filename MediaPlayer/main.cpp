#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "libraryprobe.h"
#include <QTime>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    
    QGuiApplication app(argc, argv);
    
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    
    LibraryProbe lp;
    
    QTime t;
    t.start();
    lp.explore();
    qDebug()<<t.elapsed()/1000;
    return app.exec();
}
