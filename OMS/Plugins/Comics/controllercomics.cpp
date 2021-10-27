#include "controllercomics.h"

QQmlComponent* ControllerComics::s_viewComp = nullptr;
QQmlComponent* ControllerComics::s_playlistComp = nullptr;

void ControllerComics::exec()
{
    auto comicsContext = new QQmlContext(engine()->qmlEngine().rootContext());
    comicsContext->setContextProperty("_comics", this);

    if(!s_viewComp)
        s_viewComp = new QQmlComponent(&engine()->qmlEngine(), QUrl("qrc:/comics/ComicsView.qml"));
    if(!s_playlistComp)
        s_playlistComp = new QQmlComponent(&engine()->qmlEngine(), QUrl("qrc:/comics/ComicsPlaylist.qml"));

    m_view = s_viewComp->create(comicsContext);
    m_playlist = s_playlistComp->create(comicsContext);
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

void ControllerComics::setPlaylist(PlaylistPointer) {}
void ControllerComics::setMedia(MediaPointer) {}

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
