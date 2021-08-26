#include "controllercomics.h"

void ControllerComics::exec() {}

QObject * ControllerComics::playerView() const
{
    return nullptr;
}

QObject * ControllerComics::playlistView()
{
    return nullptr;
}

QUrl ControllerComics::settingsView() const
{
    return QUrl();
}

void ControllerComics::setPlaylist(PlaylistPointer) {}
void ControllerComics::setMedia(MediaPointer) {}

MediaRole ControllerComics::role() const
{
    return MediaRole::Undefined;
}

QStringList ControllerComics::filters() const
{
    return {};
}

QString ControllerComics::rules() const
{
    return QString();
}

QSharedPointer<InterfacePlugins> ControllerComics::clone() const
{
    return QSharedPointer<InterfacePlugins>();
}
