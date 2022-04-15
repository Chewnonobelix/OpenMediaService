#include "controlleraudio.h"

QQmlComponent* ControllerAudio::s_viewComp = nullptr;
QQmlComponent* ControllerAudio::s_playlistComp = nullptr;

void ControllerAudio::exec()
{
    QFile file("./Rules/"+rules());
    if(file.open(QIODevice::ReadOnly)) {
        auto json = QJsonDocument::fromJson(file.readAll());
//        m_listModel.initColumn(json);
        file.close();
    }

    auto audioContext = new QQmlContext(engine()->qmlEngine().rootContext());
    audioContext->setContextProperty("_audio", this);
//    audioContext->setContextProperty("_pageTagModel", &m_pageTagModel);

    if(!s_viewComp)
        s_viewComp = new QQmlComponent(&engine()->qmlEngine(), QUrl("qrc:/audio/AudioPlayer.qml"));
//    if(!s_playlistComp)
//        s_playlistComp = new QQmlComponent(&engine()->qmlEngine(), QUrl("qrc:/audio/AudioPlaylist.qml"));

    auto playerContext = new QQmlContext(audioContext);
//    playerContext->setContextProperty("_player", &m_player);
    m_view = s_viewComp->create(playerContext);

    auto playlistContext = new QQmlContext(audioContext);
//    playlistContext->setContextProperty("_playlistListModel", &m_listModel);
//    playlistContext->setContextProperty("_comicsPlayList", &m_comicsPlaylist);

//    m_playlist = s_playlistComp->create(playlistContext);

    qDebug()<<s_viewComp->errorString();
}

QObject * ControllerAudio::playerView() const
{
    return m_view;
}

QObject * ControllerAudio::playlistView()
{
    return m_playlist;
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
    return MediaRole::Audio;
}

QStringList ControllerAudio::filters() const
{
    return {"mp3", "flac"};
}

QString ControllerAudio::rules() const
{
    return QString();
}

QSharedPointer<InterfacePlugins> ControllerAudio::clone() const
{
    return QSharedPointer<ControllerAudio>::create();
}

QMap<QString, QObject*> ControllerAudio::displayProperty()
{
    return {};
}
