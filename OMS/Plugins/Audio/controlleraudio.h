#pragma once

#include <Controller/Core/abstractcontroller.h>
#include <Controller/Plugins/interfaceplugins.h>

class ControllerAudio : public AbstractController, public InterfacePlugins
{
    Q_OBJECT
    Q_INTERFACES(InterfacePlugins)
    Q_PLUGIN_METADATA(IID "com.chewnonobelix.MediaPlayer.Audio")
    Q_DISABLE_COPY(ControllerAudio)

private:
    static QQmlComponent* s_viewComp;
    static QQmlComponent* s_playlistComp;
    QObject* m_view = nullptr;
    QObject* m_playlist = nullptr;

public:
    ControllerAudio() = default;
    ~ControllerAudio() override = default;

    void exec() override;

    QObject * playerView() const override;
    QObject *playlistView() override;
    QUrl settingsView() const override;

    void configureLibrary(LibraryPointer) override;
    void setPlaylist(PlaylistPointer) override;
    void setMedia(MediaPointer) override;
    QMap<QString, QObject*> displayProperty() override;

    MediaRole role() const override;
    QStringList filters() const override;
    QString rules() const override;
    inline QList<QSharedPointer<InterfaceImporter>> importers() const override{
        return  QList<QSharedPointer<InterfaceImporter>>();
    }

    QSharedPointer<InterfacePlugins> clone() const override;
};
