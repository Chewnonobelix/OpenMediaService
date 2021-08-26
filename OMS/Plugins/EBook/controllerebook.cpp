#include "controllerebook.h"

void ControllerEBook::exec() {}

QObject * ControllerEBook::playerView() const
{
    return nullptr;
}

QObject * ControllerEBook::playlistView()
{
    return nullptr;
}

QUrl ControllerEBook::settingsView() const
{
    return QUrl();
}

void ControllerEBook::setPlaylist(PlaylistPointer) {}
void ControllerEBook::setMedia(MediaPointer) {}

MediaRole ControllerEBook::role() const
{
    return MediaRole::Undefined;
}

QStringList ControllerEBook::filters() const
{
    return {};
}

QString ControllerEBook::rules() const
{
    return QString();
}

QSharedPointer<InterfacePlugins> ControllerEBook::clone() const
{
    return QSharedPointer<InterfacePlugins>();
}
