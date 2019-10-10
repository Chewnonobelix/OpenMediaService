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
    
    auto lb = m_root->findChild<QObject*>("libraryBox");
    m_library.addLibrary("Test", MediaPlayerGlobal::MediaRole::Audio);
    m_library.probeAll();
    if(!m_library.librariesName().isEmpty())
    {        
        auto lv = lb->findChild<QObject*>("libraryView");
        
        auto ll = m_library.libraries();
        QList<QVariant> list;
        for(auto it: ll)
            list<<QVariant::fromValue(it.first.data());
                
        lv->setProperty("model", list);
    }
}
