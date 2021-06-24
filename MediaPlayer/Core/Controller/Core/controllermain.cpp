#include "controllermain.h"

ControllerMain::ControllerMain() : AbstractController() {
    engine().addImportPath(QStringLiteral(QML_IMPORT_PATH));
    qDebug() << QStringLiteral(QML_IMPORT_PATH)
             << engine().importPathList();
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
                     << qmlRegisterUncreatableType<LibraryDataModel>("MediaPlayer.Model", 1, 0,
                                                          "LibraryDataModel", "Cpp owner");
    qDebug() << "ControllerLibrary"
                     << qmlRegisterUncreatableType<ControllerLibrary>("MediaPlayer.Model", 1, 0,
                                                           "ControllerLibrary", "Cpp owner");
    qDebug() << "MediaRole QML"
					 << qmlRegisterUncreatableMetaObject(
                            MediaPlayerGlobal::staticMetaObject, "MediaPlayer", 1, 0,
                            "MediaPlayer",

                            "Media Player global");
    qDebug() << "InterfacePLugin"
					 << qmlRegisterUncreatableType<InterfacePlugins>(
                            "InterfacePlugin", 1, 0, "InterfacePlugin", "Interface type");

    qDebug() << "TabManager" << qmlRegisterUncreatableType<TabManager>("MediaPlayer.Model", 1, 0,
                                                            "TabManager", "Cpp owner");

    setDb(s_settings->db());

    auto root = engine().rootContext();
    root->setContextProperty("_plugins", &s_manager);
    root->setContextProperty("_settings", s_settings);

    auto *context = new QQmlContext(root, this);

    context->setContextProperty("_main", this);
    context->setContextProperty("_db", db());
    context->setContextProperty("_tabWrapper", s_tabWrapper);

    m_librariesModel = new LibraryDataModel;

    context->setContextProperty("_librariesModel", m_librariesModel);
    connect(db(), &InterfaceSaver::librariesChanged, m_librariesModel,
            &LibraryDataModel::onUpdateLibraries);

    AbstractController::engine()->createWindow(QUrl("/Main.qml"), context);

    connect(s_settings, &ControllerSettings::dbChanged, this, &ControllerMain::onDbChanged);

    connect(m_librariesModel, &LibraryDataModel::currentIndexChanged, [this]() {
        auto index = m_librariesModel->currentIndex();
        auto cl = m_librariesModel->controller(index);
        if(cl) {
            auto current = s_tabWrapper->currentId();
            cl->setPlaylistIndex(current.toString(), 0);
            s_tabWrapper->setPlayer(index, cl->playerComp(current.toString()));
        }
    });

    connect(s_tabWrapper, &TabWrapper::currentTabChanged, [this]() {
        if(s_tabWrapper->current()) {

            auto tab = (*s_tabWrapper->current())[s_tabWrapper->currentId()];
            auto lib = tab.libIndex;
            auto play = tab.playlistIndex;

            m_librariesModel->setCurrentIndex(lib);

            if(m_librariesModel->controller(lib))
                m_librariesModel->controller(lib)->setModelIndex(play);
        }
    });

    s_manager.init();
    emit db()->librariesChanged();
}

QQmlApplicationEngine &ControllerMain::engine() {
    return AbstractController::engine()->qmlEngine();
}

void ControllerMain::onDbChanged()
{
    setDb(s_settings->db());
    connect(db(), &InterfaceSaver::librariesChanged, m_librariesModel,
            &LibraryDataModel::onUpdateLibraries);
    emit db()->librariesChanged();
}
