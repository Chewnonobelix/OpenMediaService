#include "controllerimage.h"

void ControllerImage::exec() {
    auto* root = s_engine->qmlEngine().rootContext();
    context = new QQmlContext(root);
    context->setContextProperty("_imageLibrairyModel", &m_model);
    context->setContextProperty("_imageListModel", &m_listModel);
    context->setContextProperty("_image", this);

    auto contextPlayer = new QQmlContext(context);
    auto contextPlaylist = new QQmlContext(context);


    qDebug() << "Image context";
    connect(&m_model, &LibrairyImageModel::imageChanged, this,
            &ControllerImage::setMedia);
    connect(&m_timer, &QTimer::timeout, this, &ControllerImage::onTimeout);
    m_timer.setInterval(2000);

    m_playlist = new QQmlComponent(&(s_engine->qmlEngine()),
                                   QUrl("qrc:/image/ImagePlaylist.qml"));
    m_playlistObj = m_playlist->create(contextPlaylist);

    m_player = new QQmlComponent(&(s_engine->qmlEngine()),
                                 QUrl("qrc:/image/ImagePlayer.qml"));
    m_playerObj = m_player->create(contextPlayer);
}

QObject *ControllerImage::playerView() const {
    return m_playerObj;
}

QObject *ControllerImage::playlistView() {
    return m_playlistObj;
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

void ControllerImage::playing(int index) {
    stop();
    m_current->setCurrentIndex(index);
    m_timer.start();
}

void ControllerImage::stop() { m_timer.stop(); }

void ControllerImage::onTimeout() { m_current->next(); }

QSharedPointer<InterfacePlugins> ControllerImage::clone() const {
    return QSharedPointer<ControllerImage>::create();
}


QUrl ControllerImage::settingsView() const {
    return QUrl("qrc:/image/ImageSettings.qml");
}
