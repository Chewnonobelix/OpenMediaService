#include "controllerimage.h"

void ControllerImage::exec() {
	auto context = m_engine->qmlEngine().rootContext();
	context->setContextProperty("_imageLibrairyModel", &m_model);
	context->setContextProperty("_image", this);

	connect(&m_model, &LibrairyImageModel::imageChanged, this,
					&ControllerImage::setMedia);
	connect(&m_timer, &QTimer::timeout, this, &ControllerImage::onTimeout);
	m_timer.setInterval(2000);
}

QString ControllerImage::playerView() const {
	return "qrc:/image/ImagePlayer.qml";
}

QString ControllerImage::playlistView() const {

	return "qrc:/image/ImagePlaylist.qml";
}

void ControllerImage::setPlaylist(PlaylistPointer p) {
	m_current = p;
	m_model.setPlaylist(p);
	connect(m_current.data(), &PlayList::play, this, &ControllerImage::setMedia,
					Qt::UniqueConnection);
}

void ControllerImage::setMedia(MediaPointer m) {
	if (m) {
		emit play(m->path());
		m->setCount(m->count() + 1);
	} else {
		m_timer.stop();
	}
}

MediaRole ControllerImage::role() const { return MediaRole::Image; }

void ControllerImage::onCurrentIndexChanged(int i) {
	m_timer.stop();
	if (i > 0)
		m_current->next();
	else
		m_current->prev();
}

QStringList ControllerImage::filters() const {
	return {"jpg", "jpeg", "bmp", "png"};
}

void ControllerImage::playing() {
	stop();
	m_current->setCurrentIndex(-1);
	m_timer.start();
}

void ControllerImage::stop() { m_timer.stop(); }

void ControllerImage::onTimeout() { m_current->next(); }

QSharedPointer<InterfacePlugins> ControllerImage::clone() const {
	return QSharedPointer<ControllerImage>::create();
}
