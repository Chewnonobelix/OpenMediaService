#include "controllercomics.h"

QQmlComponent* ControllerComics::s_viewComp = nullptr;
QQmlComponent* ControllerComics::s_playlistComp = nullptr;

ControllerComics::ControllerComics(): AbstractController(), m_pageTagModel(this)
{}

void ControllerComics::exec()
{
    m_player.setSplit(s_settings->value("Comics/split").toBool());
    QFile file("./Rules/"+rules());
    if(file.open(QIODevice::ReadOnly)) {
        auto json = QJsonDocument::fromJson(file.readAll());
        m_listModel.initColumn(json);
        file.close();
    }

    auto comicsContext = new QQmlContext(engine()->qmlEngine().rootContext());
    comicsContext->setContextProperty("_comics", this);
    comicsContext->setContextProperty("_pageTagModel", &m_pageTagModel);

    if(!s_viewComp)
        s_viewComp = new QQmlComponent(&engine()->qmlEngine(), QUrl("qrc:/comics/ComicsView.qml"));
    if(!s_playlistComp)
        s_playlistComp = new QQmlComponent(&engine()->qmlEngine(), QUrl("qrc:/comics/ComicsPlaylist.qml"));

    auto playerContext = new QQmlContext(comicsContext);
    playerContext->setContextProperty("_player", &m_player);
    m_view = s_viewComp->create(playerContext);

    auto playlistContext = new QQmlContext(comicsContext);
    playlistContext->setContextProperty("_playlistListModel", &m_listModel);
    playlistContext->setContextProperty("_comicsPlayList", &m_comicsPlaylist);

    m_playlist = s_playlistComp->create(playlistContext);

    connect(s_settings, &ControllerSettings::settingsChanged, [this]() {
        m_player.setSplit(s_settings->value("Comics/split").toBool());
    });

}

QObject * ControllerComics::playerView() const
{
    return m_view;
}

QObject * ControllerComics::playlistView()
{
    return m_playlist;
}

QUrl ControllerComics::settingsView() const
{
    return QUrl("qrc:/comics/ComicsSettings.qml");
}

void ControllerComics::configureLibrary(LibraryPointer lp)
{
    m_library = lp;
    m_library->setMetadata("tagsList", QStringList{"tags", "pageTags"});

    emit lp->libraryChanged();

    connect(&m_pageTagModel, &TagModel::s_addTag, [this](auto tag) {
        auto tags = m_library->metaData<QList<MediaPlayerGlobal::Tag>>("pageTags");
        tags<<tag;
        m_library->setMetadata("pageTags", tags);
        m_pageTagModel.setModel(tags);
    });

    connect(&m_pageTagModel, &TagModel::s_removeTag, [this](auto tag) {
        auto tags = m_library->metaData<QList<MediaPlayerGlobal::Tag>>("pageTags");

        std::remove_if(tags.begin(), tags.end(), [tag](auto it) {
            return it.first == tag.first;
        });

        m_library->setMetadata("pageTags", tags);
        m_pageTagModel.setModel(tags);
    });

    connect(&m_pageTagModel, &TagModel::s_editTag, [this](auto tag) {
        auto tags = m_library->metaData<QList<MediaPlayerGlobal::Tag>>("pageTags");

        auto te = std::find_if(tags.begin(), tags.end(), [tag](auto it) {
            return it.first == tag.first;
        });

        if(te != tags.end())
            te->second = tag.second;

        m_library->setMetadata("pageTags", tags);
        m_pageTagModel.setModel(tags);
    });

    qDebug()<<m_library->metaData<QList<MediaPlayerGlobal::Tag>>("pageTags");
    m_pageTagModel.setModel(m_library->metaData<QList<MediaPlayerGlobal::Tag>>("pageTags"));
}

void ControllerComics::setPlaylist(PlaylistPointer p)
{
    disconnect(m_playlistPointer.data(), &PlayList::play, this, &ControllerComics::setMedia);
    connect(p.data(), &PlayList::play, this, &ControllerComics::setMedia,
            Qt::UniqueConnection);
    m_listModel.setPlaylist(p);
    m_playlistPointer = p;

    QtConcurrent::run([this]() -> void {
        for(auto it: *m_playlistPointer) {
            m_medias[it->id()] = ComicsMedia(it);
            m_medias[it->id()].load();
            m_medias[it->id()].initComicsInfo();
        }
    }).then([p, this]() {
            m_comicsPlaylist.init(p, m_medias.values());
        });
}

void ControllerComics::setMedia(MediaPointer m)
{
    m_medias[m->id()].load();
    m_player.play(m);
}

MediaRole ControllerComics::role() const
{
    return MediaRole::Comics;
}

QStringList ControllerComics::filters() const
{
    return {"cbz", "cbr"};
}

QString ControllerComics::rules() const
{
    return "comicsrules.json";
}

QSharedPointer<InterfacePlugins> ControllerComics::clone() const
{
    return factory<ControllerComics>();
}

QList<QSharedPointer<InterfaceImporter>> ControllerComics::importers() const
{
    QList<QSharedPointer<InterfaceImporter>> ret;
    ret<<factory<ComicsRackImporter>();
    return ret;
}

QMap<QString, QObject*> ControllerComics::displayProperty()
{
    auto context = new QQmlContext(engine()->qmlEngine().rootContext());
    auto component = new QQmlComponent(&engine()->qmlEngine(), QUrl("qrc:/comics/ComicsProperties.qml"));
    auto obj = component->create(context);
    QMap<QString, QObject*> ret;

    return ret;
}
