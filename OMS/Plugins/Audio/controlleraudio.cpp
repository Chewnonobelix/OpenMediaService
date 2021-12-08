#include "controlleraudio.h"

void ControllerAudio::exec() {}

QObject * ControllerAudio::playerView() const
{
    return nullptr;
}

QObject * ControllerAudio::playlistView()
{
    return nullptr;
}

QUrl ControllerAudio::settingsView() const
{
    return QUrl();
}

void ControllerAudio::configureLibrary(LibraryPointer) {}
void ControllerAudio::setPlaylist(PlaylistPointer) {}
void ControllerAudio::setMedia(MediaPointer) {}

MediaRole ControllerAudio::role() const
{
    return MediaRole::Undefined;
}

QStringList ControllerAudio::filters() const
{
    return {};
}

QString ControllerAudio::rules() const
{
    return QString();
}

QSharedPointer<InterfacePlugins> ControllerAudio::clone() const
{
    return QSharedPointer<InterfacePlugins>();
}
