#include "ControllerImage.hpp"

void ControllerImage::exec() {}

QString ControllerImage::playerView() const {
	return "qrc:/image/ImagePlaylist.qml";
}

QString ControllerImage::libraryView() const { return ""; }

void ControllerImage::setLibrary(LibraryPointer) {}

void ControllerImage::setMedia(MediaPointer) {}
