#include "controllercomics.h"

QQmlComponent* ControllerComics::s_viewComp = nullptr;
QQmlComponent* ControllerComics::s_playlistComp = nullptr;

void ControllerComics::exec()
{
    m_player.setSplit(s_settings->value("Comics/split").toBool());
    QFile file("./Rules/"+rules());
    if(file.open(QIODevice::ReadOnly)) {
        auto json = QJsonDocument::fromJson(file.readAll());
        m_listModel.initColumn(json);
        file.close();
    }

    auto comicsContext = new QQmlContext(engine()->qmlEngine().rootContext());
    comicsContext->setContextProperty("_comics", this);

    if(!s_viewComp)
        s_viewComp = new QQmlComponent(&engine()->qmlEngine(), QUrl("qrc:/comics/ComicsView.qml"));
    if(!s_playlistComp)
        s_playlistComp = new QQmlComponent(&engine()->qmlEngine(), QUrl("qrc:/comics/ComicsPlaylist.qml"));

    auto playerContext = new QQmlContext(comicsContext);
    playerContext->setContextProperty("_player", &m_player);
    m_view = s_viewComp->create(playerContext);

    auto playlistContext = new QQmlContext(comicsContext);
    playlistContext->setContextProperty("_playlistListModel", &m_listModel);

    m_playlist = s_playlistComp->create(playlistContext);

    connect(s_settings, &ControllerSettings::settingsChanged, [this]() {
        m_player.setSplit(s_settings->value("Comics/split").toBool());
    });
}

QObject * ControllerComics::playerView() const
{
    return m_view;
}

QObject * ControllerComics::playlistView()
{
    return m_playlist;
}

QUrl ControllerComics::settingsView() const
{
    return QUrl("qrc:/comics/ComicsSettings.qml");
}

void ControllerComics::setPlaylist(PlaylistPointer p)
{
    connect(p.data(), &PlayList::play, this, &ControllerComics::setMedia,
            Qt::UniqueConnection);
    m_listModel.setPlaylist(p);
}

void ControllerComics::setMedia(MediaPointer m)
{
    m_player.play(m);
}

MediaRole ControllerComics::role() const
{
    return MediaRole::Comics;
}

QStringList ControllerComics::filters() const
{
    return {"cbz", "cbr"};
}

QString ControllerComics::rules() const
{
    return "comicsrules.json";
}

QSharedPointer<InterfacePlugins> ControllerComics::clone() const
{
    return factory<ControllerComics>();
}

QList<QSharedPointer<InterfaceImporter>> ControllerComics::importers() const
{
    QList<QSharedPointer<InterfaceImporter>> ret;
    ret<<factory<ComicsRackImporter>();
    return ret;
}
