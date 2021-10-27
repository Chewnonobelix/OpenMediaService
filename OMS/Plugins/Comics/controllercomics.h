#pragma once

#include <Controller/Core/abstractcontroller.h>
#include <Controller/Plugins/interfaceplugins.h>

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

public:
    ControllerComics() = default;
    ~ControllerComics() override = default;

    void exec() override;

    QObject * playerView() const override;
    QObject *playlistView() override;
    QUrl settingsView() const override;
    void setPlaylist(PlaylistPointer) override;
    void setMedia(MediaPointer) override;

    MediaRole role() const override;
    QStringList filters() const override;
    QString rules() const override;

    QSharedPointer<InterfacePlugins> clone() const override;
};
