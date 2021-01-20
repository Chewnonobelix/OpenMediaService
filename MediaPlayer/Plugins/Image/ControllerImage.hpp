#pragma once

#include <Controller/Core/abstractcontroller.h>
#include <Controller/Plugins/interfaceplugins.h>

#include "ImageModel.hpp"

class ControllerImage : public AbstractController, public InterfacePlugins {
	Q_OBJECT
	Q_INTERFACES(InterfacePlugins)
	Q_PLUGIN_METADATA(IID "com.chewnonobelix.MediaPlayer.Image")

private:
	PlaylistPointer m_current;
	ImageModel m_model;

public:
	ControllerImage() = default;
	ControllerImage(const ControllerImage &) = default;
	~ControllerImage() override = default;

	void exec() override;

	QString playerView() const override;
	QString playlistView() const override;
	void setPlaylist(PlaylistPointer) override;
	void setMedia(MediaPointer) override;

	MediaRole role() const override;

public slots:
	void onCurrentIndexChanged(int);

signals:
	void play(QString);
};
