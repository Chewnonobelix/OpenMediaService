#include "controllervideo.h"

void ControllerVideo::exec() {}

QObject * ControllerVideo::playerView() const {
    static QQmlComponent ret(&(engine()->qmlEngine()), "qrc:/video/VideoPlayer.qml");
    return ret.create();
}

QObject *ControllerVideo::playlistView() {
    static QQmlComponent ret(&(engine()->qmlEngine()), "qrc:/video/VideoPlaylist.qml");
    return ret.create();
}

void ControllerVideo::setPlaylist(PlaylistPointer) {}

void ControllerVideo::setMedia(MediaPointer) {}

MediaRole ControllerVideo::role() const { return MediaRole::Video; }

QStringList ControllerVideo::filters() const {
	return {"ts", "mp4", "mkv", "avi"};
}

QSharedPointer<InterfacePlugins> ControllerVideo::clone() const {
	return QSharedPointer<ControllerVideo>::create();
}

QUrl ControllerVideo::settingsView() const {
    return QUrl();
}

QString ControllerVideo::rules() const
{
    return "";
}
