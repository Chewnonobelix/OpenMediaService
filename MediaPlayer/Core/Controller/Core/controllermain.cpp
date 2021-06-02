#include "controllermain.h"

ControllerMain::ControllerMain() : AbstractController() {
    engine().addImportPath(QStringLiteral(QML_IMPORT_PATH));
    qDebug() << QStringLiteral(QML_IMPORT_PATH)
             << engine().importPathList();
    m_manager.init();
}

void ControllerMain::exec() {
    qDebug() << "DataXml" << qRegisterMetaType<DataXml>();
    qDebug() << "DataJson" << qRegisterMetaType<DataJson>();
    qDebug() << "MediaPlayer::MediaRole"
					 << qRegisterMetaType<MediaPlayerGlobal::MediaRole>();

    qDebug() << "LibraryProbe"
					 << qmlRegisterUncreatableType<LibraryProbe>(
                            "MediaPlayer", 1, 0, "LibraryProbe", "Cpp owner");
    qDebug() << "Library"
					 << qmlRegisterUncreatableType<Library>("MediaPlayer", 1, 0,
                                                            "Library", "Cpp owner");
    qDebug() << "Media"
                     << qmlRegisterUncreatableType<Media>("MediaPlayer", 1, 0,
                                                            "Media", "Cpp owner");
    qDebug() << "Playlist"
                     << qmlRegisterUncreatableType<PlayList>("MediaPlayer", 1, 0,
                                                          "Playlist", "Cpp owner");

    qDebug() << "LibraryDataModel"
					 << qmlRegisterType<LibraryDataModel>("MediaPlayer.Model", 1, 0,
                                                          "LibraryDataModel");
    qDebug() << "ControllerLibrary"
					 << qmlRegisterType<ControllerLibrary>("MediaPlayer.Model", 1, 0,
                                                           "ControllerLibrary");
    qDebug() << "MediaRole QML"
					 << qmlRegisterUncreatableMetaObject(
                            MediaPlayerGlobal::staticMetaObject, "MediaPlayer", 1, 0,
                            "MediaPlayer",

                            "Media Player global");
    qDebug() << "InterfacePLugin"
					 << qmlRegisterUncreatableType<InterfacePlugins>(
                            "InterfacePlugin", 1, 0, "InterfacePlugin", "Interface type");

    qDebug() << "TabManager" << qmlRegisterType<TabManager>("MediaPlayer.Model", 1, 0,
                                            "TabManager");

    setDb(m_settings->db());

    auto *context = engine().rootContext();
    context->setContextProperty("_main", this);
    context->setContextProperty("_db", db());
    context->setContextProperty("_plugins", &m_manager);
    context->setContextProperty("_settings", m_settings);
    context->setContextProperty("_tabWrapper", m_tabWrapper);

    m_librariesModel = new LibraryDataModel;

    context->setContextProperty("_librariesModel", m_librariesModel);
    connect(db(), &InterfaceSaver::librariesChanged, m_librariesModel,
            &LibraryDataModel::onUpdateLibraries);

    m_engine->createWindow(QUrl("/Main.qml"));

    connect(m_settings, &ControllerSettings::dbChanged, this, &ControllerMain::onDbChanged);
    emit db()->librariesChanged();

    connect(m_librariesModel, &LibraryDataModel::currentIndexChanged, [this]() {
       auto index = m_librariesModel->currentIndex();
       auto cl = m_librariesModel->controller(index);
       auto current = m_tabWrapper->currentId();
       cl->setPlaylistIndex(current.toString(), 0);
       m_tabWrapper->setPlayer(cl->playerComp(current.toString()));
    });
}

QQmlApplicationEngine &ControllerMain::engine() {
    return m_engine->qmlEngine();
}

void ControllerMain::onDbChanged()
{
    setDb(m_settings->db());
    connect(db(), &InterfaceSaver::librariesChanged, m_librariesModel,
            &LibraryDataModel::onUpdateLibraries);
    emit db()->librariesChanged();
}
