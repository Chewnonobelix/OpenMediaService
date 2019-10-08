#include "controllermain.h"

ControllerMain::ControllerMain()
{
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&m_engine, &QQmlApplicationEngine::objectCreated,
                     QCoreApplication::instance(), [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    m_engine.load(url);

    m_root = m_engine.rootObjects().first();
    
    m_library.probeAll();
    
    auto list = m_library.m_libs.first().second->selectMedia();
    QList<QVariant> lm;
    for(auto it: list)
        lm<<QVariant::fromValue(*it);
    
    auto o = m_root->findChild<QObject*>("libraryView");
    o->setProperty("model", lm);
    
}
