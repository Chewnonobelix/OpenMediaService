#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Model/libraryprobe.h"
#include "Model/library.h"

#include "Controller/xmldatabase.h"
#include "Controller/controllerlibrary.h"
#include <QTime>


int main(int argc, char *argv[])
{
    QString testDir = "E:\\Cloud\\Scan";

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    
    QGuiApplication app(argc, argv);
    qRegisterMetaType<XmlDatabase>();
    qDebug()<<QMetaType::type("XmlDatabase");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    
    ControllerLibrary cl;
    cl.addLibrary("Test", MediaRole::Audio);
    cl.probeAll();
    
    
    return app.exec();
}
