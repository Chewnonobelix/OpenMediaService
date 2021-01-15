#include "ControllerImage.hpp"

void ControllerImage::exec() {}

QString ControllerImage::playerView() const {
	return "qrc:/image/ImagePlayer.qml";
}

QString ControllerImage::playlistView() const {
	return "qrc:/image/ImagePlaylist.qml";
}

void ControllerImage::setPlaylist(PlaylistPointer p) {
	qDebug() << "Dsiplay " << p->name() << p->count();
	m_current = p;
}

void ControllerImage::setMedia(MediaPointer) {}

MediaRole ControllerImage::role() const { return MediaRole::Image; }
