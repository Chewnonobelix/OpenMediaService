#include "controllermain.h"

Q_LOGGING_CATEGORY(mainlog, "main.log")
Q_LOGGING_CATEGORY(mainregister, "main.register")

ControllerMain::ControllerMain() : AbstractController() {
    engine().addImportPath(QStringLiteral(QML_IMPORT_PATH));
    qCDebug(mainlog) << QStringLiteral(QML_IMPORT_PATH)
                     << engine().importPathList();
    QDir dir;
    dir.mkdir("temp");
    dir.mkdir("cache");
}

ControllerMain::~ControllerMain()
{
    try
    {
       setDb("");
    }
    catch(QString)
    {

    }

    QDir dir;
    dir.cd("temp");
    dir.removeRecursively();
}

void ControllerMain::exec() {
    qCDebug(mainregister) << "DataXml" << qRegisterMetaType<DataXml>();
    qCDebug(mainregister) << "DataJson" << qRegisterMetaType<DataJson>();
    qCDebug(mainregister) << "DataSql" << qRegisterMetaType<DataSql>();
    qCDebug(mainregister) << "MediaPlayer::MediaRole"
                          << qRegisterMetaType<MediaPlayerGlobal::MediaRole>();

    qCDebug(mainregister) << "LibraryProbe"
                          << qmlRegisterUncreatableType<LibraryProbe>(
                                 "MediaPlayer", 1, 0, "LibraryProbe", "Cpp owner");
    qCDebug(mainregister) << "Library"
                          << qmlRegisterUncreatableType<Library>("MediaPlayer", 1, 0,
                                                                 "Library", "Cpp owner");
    qCDebug(mainregister) << "Media"
                          << qmlRegisterUncreatableType<Media>("MediaPlayer", 1, 0,
                                                               "Media", "Cpp owner");
    qCDebug(mainregister) << "Playlist"
                          << qmlRegisterUncreatableType<PlayList>("MediaPlayer", 1, 0,
                                                                  "Playlist", "Cpp owner");
    qCDebug(mainregister) << "SmartPlaylist"
                          << qmlRegisterUncreatableType<SmartPlaylist>("MediaPlayer", 1, 0,
                                                                       "SmartPlaylist", "Cpp owner");

    qCDebug(mainregister) << "SmartGroup"
                          << qmlRegisterUncreatableType<SmartGroup>("MediaPlayer", 1, 0,
                                                                    "smartGroup", "Cpp owner");

    qCDebug(mainregister) << "LibraryDataModel"
                          << qmlRegisterUncreatableType<LibraryDataModel>("MediaPlayer.Model", 1, 0,
                                                                          "LibraryDataModel", "Cpp owner");

    qCDebug(mainregister) << "SmartModel"
                          << qmlRegisterType<SmartModel>("MediaPlayer.Model", 1, 0,
                                                         "SmartModel");

    qCDebug(mainregister) << "ControllerLibrary"
                          << qmlRegisterUncreatableType<ControllerLibrary>("MediaPlayer.Model", 1, 0,
                                                                           "ControllerLibrary", "Cpp owner");
    qCDebug(mainregister) << "MediaRole QML"
                          << qmlRegisterUncreatableMetaObject(
                                 MediaPlayerGlobal::staticMetaObject, "MediaPlayer", 1, 0,
                                 "MediaPlayer",

                                 "Media Player global");
//    qCDebug(mainregister)<< "InterfacePLugin"
//                          << qmlRegisterUncreatableType<InterfacePlugins>(
//                                 "InterfacePlugin", 1, 0, "InterfacePlugin", "Interface type");

    qCDebug(mainregister) << "TabManager" << qmlRegisterUncreatableType<TabManager>("MediaPlayer.Model", 1, 0,
                                                                                    "TabManager", "Cpp owner");

//    qCDebug(mainregister) << "AbstractRule" << qmlRegisterUncreatableType<AbstractRule>("MediaPlayer.Model", 1, 0, "abstractRule", "Cpp owner");

    qCDebug(mainregister) << "PlaylistListModel" << qmlRegisterUncreatableType<PlaylistListModel>("MediaPlayer.Model", 1, 0, "PlaylistListModel", "Cpp owner");
    qCDebug(mainregister) << "OrderDisplayModel" << qmlRegisterUncreatableType<OrderDisplayModel>("MediaPlayer.Model", 1, 0, "OrderDisplayModel", "Cpp owner");
    qCDebug(mainregister) << "TagModel" << qmlRegisterUncreatableType<TagModel>("MediaPlayer.Model", 1, 0, "TagModel", "Cpp owner");
    setDb(s_settings->db());

    auto root = engine().rootContext();
    root->setContextProperty("_plugins", &s_manager);
    root->setContextProperty("_settings", s_settings);


    m_librariesModel = new LibraryDataModel;

    root->setContextProperty("_tabWrapper", s_tabWrapper);
    root->setContextProperty("_db", db());
    root->setContextProperty("_librariesModelGlobal", m_librariesModel);


    auto *context = new QQmlContext(root, this);
    context->setContextProperty("_librariesModel", m_librariesModel);
    context->setContextProperty("_main", this);
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
