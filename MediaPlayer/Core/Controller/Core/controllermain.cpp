#include "controllermain.h"

ControllerMain::ControllerMain()
    : AbstractController(), m_engine(this, QStringLiteral(QML_SOURCE) + "/View")
{}

void ControllerMain::exec()
{
    qDebug() << "DataXml" << qRegisterMetaType<DataXml>();
    qDebug() << "Library" << qmlRegisterType<Library>("MediaPlayer", 1, 0, "Library");
    qDebug() << "LibraryDataModel"
             << qmlRegisterType<LibraryDataModel>("MediaPlayer", 1, 0, "LibraryDataModel");
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
    context->setContextProperty("_libraryModel", &ldm);

    connect(db(), &InterfaceSaver::addLibrary, this, &ControllerMain::onAddLibrary);

    m_engine.createWindow(QUrl("/Main.qml"));

    for (auto it : db()->selectLibrary())
        ldm.insertData(it);
}

QQmlApplicationEngine &ControllerMain::engine()
{
    return m_engine.qmlEngine();
}

void ControllerMain::onAddLibrary(LibraryPointer p)
{
    ldm.insertData(p);
    //    auto list = db()->selectLibrary();

    //    QList<Library *> model;
    //    for (auto it : list)
    //        model << it.data();

    //    std::sort(model.begin(), model.end(), [](Library *l1, Library *l2) {
    //        return l1->role() < l2->role() && l1->name() < l2->name();
    //    });

    //    emit libraryModelChanged(model);
}
