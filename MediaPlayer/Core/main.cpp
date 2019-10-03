#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
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
    qmlRegisterType<Media>();
    
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
//    cl.addLibrary("Test", MediaRole::Audio);
    cl.probeAll();
    
    auto list = cl.m_libs.first().second->selectMedia();
    QList<QVariant> lm;
    for(auto it: list)
        lm<<QVariant::fromValue(*it);
    
    auto o = engine.rootObjects().first()->findChild<QObject*>("libraryView");
    o->setProperty("model", lm);
    
    return app.exec();
}
