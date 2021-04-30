#pragma once

#include <Controller/Core/abstractcontroller.h>
#include <Controller/Plugins/interfaceplugins.h>

#include "librairyimagemodel.h"
#include "imagelistmodel.h"

class ControllerImage : public AbstractController, public InterfacePlugins {
	Q_OBJECT
	Q_INTERFACES(InterfacePlugins)
	Q_PLUGIN_METADATA(IID "com.chewnonobelix.MediaPlayer.Image")

private:
	PlaylistPointer m_current;

    LibrairyImageModel m_model;
    ImageListModel m_listModel;

	QTimer m_timer;
	QPointer<QQmlComponent> m_playlist;
    QPointer<QQmlComponent> m_player;

public:
	ControllerImage() = default;
	ControllerImage(const ControllerImage &) = default;
	~ControllerImage() override = default;

	void exec() override;

    QQmlComponent * playerView() const override;
	QQmlComponent *playlistView() override;
    QUrl settingsView() const override;

	void setPlaylist(PlaylistPointer) override;
	void setMedia(MediaPointer) override;

	MediaRole role() const override;
	QStringList filters() const override;
	QSharedPointer<InterfacePlugins> clone() const override;

public slots:
	void onCurrentIndexChanged(int);
    void playing(int = -1);
	void stop();
	void onTimeout();

signals:
	void play(QString);
};
