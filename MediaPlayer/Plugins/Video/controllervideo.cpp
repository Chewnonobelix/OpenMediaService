#include "controllervideo.h"

void ControllerVideo::exec() {}

QQmlComponent * ControllerVideo::playerView() const {
    static QQmlComponent ret(&(m_engine->qmlEngine()), "qrc:/video/VideoPlayer.qml");
    return &ret;
//	return "qrc:/video/VideoPlayer.qml";
}

QQmlComponent *ControllerVideo::playlistView() {
    static QQmlComponent ret(&(m_engine->qmlEngine()), "qrc:/video/VideoPlaylist.qml");
	return &ret;
	//	return "qrc:/video/VideoPlaylist.qml";
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
