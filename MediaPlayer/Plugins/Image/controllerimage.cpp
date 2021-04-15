#include "controllerimage.h"

void ControllerImage::exec() {
    auto context = m_engine->qmlEngine().rootContext();
    context->setContextProperty("_imageLibrairyModel", &m_model);
    context->setContextProperty("_imageListModel", &m_listModel);
    context->setContextProperty("_image", this);

	qDebug() << "Image context";
	connect(&m_model, &LibrairyImageModel::imageChanged, this,
					&ControllerImage::setMedia);
	connect(&m_timer, &QTimer::timeout, this, &ControllerImage::onTimeout);
	m_timer.setInterval(2000);

	static QUuid id = QUuid::createUuid();

	context->setContextProperty("wid", id);
	context->setContextProperty(id.toString() + "_playlist", &m_model);
	m_playlist = new QQmlComponent(&(m_engine->qmlEngine()),
																 QUrl("qrc:/image/ImagePlaylist.qml"));
	m_playlist->create(context);

	m_player = new QQmlComponent(&(m_engine->qmlEngine()),
															 QUrl("qrc:/image/ImagePlayer.qml"));
	m_player->create(context);
}

QQmlComponent *ControllerImage::playerView() const {
	return m_player;
	//    return "qrc:/image/ImagePlayer.qml";
}

QQmlComponent *ControllerImage::playlistView() {
	return m_playlist;
	//	return "qrc:/image/ImagePlaylist.qml";
}

void ControllerImage::setPlaylist(PlaylistPointer p) {
    m_current = p;
    m_model.setPlaylist(p);
    m_listModel.setPLaylist(p);

    if(p)
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
