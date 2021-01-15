#include "ControllerImage.hpp"

void ControllerImage::exec() {
	auto context = m_engine->qmlEngine().rootContext();
	context->setContextProperty("_imageModel", &m_model);
	context->setContextProperty("_image", this);

	connect(&m_model, &ImageModel::currentIndexChanged, this,
					&ControllerImage::onCurrentIndexChanged);
}

QString ControllerImage::playerView() const {
	return "qrc:/image/ImagePlayer.qml";
}

QString ControllerImage::playlistView() const {

	return "qrc:/image/ImagePlaylist.qml";
}

void ControllerImage::setPlaylist(PlaylistPointer p) {
	qDebug() << "Dsiplay " << p->name() << p->count();
	m_current = p;
	m_model.setPlaylist(p);
}

void ControllerImage::setMedia(MediaPointer m) { emit play(m->path()); }

MediaRole ControllerImage::role() const { return MediaRole::Image; }

void ControllerImage::onCurrentIndexChanged(int i) {
	setMedia((*m_current)[i]);
}
