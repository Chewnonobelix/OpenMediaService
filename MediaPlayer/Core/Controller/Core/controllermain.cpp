#include "controllermain.h"

ControllerMain::ControllerMain()
    : AbstractController(), m_engine(this, QStringLiteral(QML_SOURCE) + "/View"),
      m_libraries(engine())
{}

void ControllerMain::exec()
{
    qDebug() << "DataXml" << qRegisterMetaType<DataXml>();
    qDebug() << "Library" << qmlRegisterType<Library>("MediaPlayer", 1, 0, "Library");
    qDebug() << "LibraryDataModel"
             << qmlRegisterType<LibraryDataModel>("MediaPlayer.Model", 1, 0, "LibraryDataModel");
    qDebug() << "MediaRole QML"
             << qmlRegisterUncreatableMetaObject(MediaPlayerGlobal::staticMetaObject,
                                                 "MediaPlayer",
                                                 1,
                                                 0,
                                                 "MediaPlayer",

                                                 "Media PLayer global");

    setDb("DataXml");
    auto *context = engine().rootContext();
    context->setContextProperty("_main", this);
    context->setContextProperty("_db", db());

    m_libraries.exec();
    m_engine.createWindow(QUrl("/Main.qml"));
}

QQmlApplicationEngine &ControllerMain::engine()
{
    return m_engine.qmlEngine();
}
