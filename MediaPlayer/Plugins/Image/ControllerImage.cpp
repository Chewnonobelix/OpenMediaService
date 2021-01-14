#include "ControllerImage.hpp"

void ControllerImage::exec() {}

QString ControllerImage::playerView() const {
	return "qrc:/image/ImagePlayer.qml";
}

QString ControllerImage::libraryView() const {
	return "qrc:/image/ImagePlaylist.qml";
}

void ControllerImage::setLibrary(LibraryPointer) {}

void ControllerImage::setMedia(MediaPointer) {}

MediaRole ControllerImage::role() const { return MediaRole::Image; }
