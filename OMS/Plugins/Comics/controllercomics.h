#pragma once

#include <QQuickWindow>

#include <Controller/Core/abstractcontroller.h>
#include <Controller/Plugins/interfaceplugins.h>

#include <Controller/DataModel/playlistlistmodel.h>
#include <Controller/DataModel/tagmodel.h>

#include "comicsplayer.h"
#include "comicsrackimporter.h"
#include "comicsplaylist.h"
#include "comicsmedia.h"

class ControllerComics : public AbstractController, public InterfacePlugins
{
    Q_OBJECT
    Q_INTERFACES(InterfacePlugins)
    Q_PLUGIN_METADATA(IID "com.chewnonobelix.MediaPlayer.Comics")
    Q_DISABLE_COPY(ControllerComics)

private:
    static QQmlComponent* s_viewComp;
    static QQmlComponent* s_playlistComp;
    QObject* m_view = nullptr;
    QObject* m_playlist = nullptr;

    ComicsPlayer m_player;
    PlaylistListModel m_listModel;
    ComicsPlaylist m_comicsPlaylist;

    QMap<QUuid, ComicsMedia> m_medias;
    PlaylistPointer m_playlistPointer;
    LibraryPointer m_library;
    TagModel m_pageTagModel;

public:
    ControllerComics();
    ~ControllerComics() override = default;

    void exec() override;

    QObject * playerView() const override;
    QObject *playlistView() override;
    QUrl settingsView() const override;

    void configureLibrary(LibraryPointer) override;
    void setPlaylist(PlaylistPointer) override;
    void setMedia(MediaPointer) override;
    void displayProperty(MediaPointer) override;

    MediaRole role() const override;
    QStringList filters() const override;
    QString rules() const override;
    QList<QSharedPointer<InterfaceImporter>> importers() const override;

    QSharedPointer<InterfacePlugins> clone() const override;
};
