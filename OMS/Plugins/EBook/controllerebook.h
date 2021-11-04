#pragma once

#include <Controller/Core/abstractcontroller.h>
#include <Controller/Plugins/interfaceplugins.h>

class ControllerEBook : public AbstractController, public InterfacePlugins
{
    Q_INTERFACES(InterfacePlugins)
    Q_PLUGIN_METADATA(IID "com.chewnonobelix.MediaPlayer.EBook")
    Q_DISABLE_COPY(ControllerEBook)

public:
    ControllerEBook() = default;
    ~ControllerEBook() override = default;

    void exec() override;

    QObject * playerView() const override;
    QObject *playlistView() override;
    QUrl settingsView() const override;
    void setPlaylist(PlaylistPointer) override;
    void setMedia(MediaPointer) override;

    MediaRole role() const override;
    QStringList filters() const override;
    QString rules() const override;
    inline QList<QSharedPointer<InterfaceImporter>> importers() const override{
        return  QList<QSharedPointer<InterfaceImporter>>();
    }

    QSharedPointer<InterfacePlugins> clone() const override;
};
