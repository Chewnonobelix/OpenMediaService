#pragma once

#include <Controller/Core/abstractcontroller.h>
#include <Controller/Plugins/interfaceplugins.h>

#include "librairyimagemodel.h"

class ControllerImage : public AbstractController, public InterfacePlugins {
	Q_OBJECT
	Q_INTERFACES(InterfacePlugins)
	Q_PLUGIN_METADATA(IID "com.chewnonobelix.MediaPlayer.Image")

private:
	PlaylistPointer m_current;
	LibrairyImageModel m_model;
	QTimer m_timer;
	QPointer<QQmlComponent> m_playlist;

public:
	ControllerImage() = default;
	ControllerImage(const ControllerImage &) = default;
	~ControllerImage() override = default;

	void exec() override;

	QString playerView() const override;
	QQmlComponent *playlistView() override;
	void setPlaylist(PlaylistPointer) override;
	void setMedia(MediaPointer) override;

	MediaRole role() const override;
	QStringList filters() const override;
	QSharedPointer<InterfacePlugins> clone() const override;

public slots:
	void onCurrentIndexChanged(int);
	void playing();
	void stop();
	void onTimeout();

signals:
	void play(QString);
};
