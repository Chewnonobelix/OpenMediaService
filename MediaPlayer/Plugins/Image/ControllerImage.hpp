#pragma once

#include <Controller/Core/abstractcontroller.h>
#include <Controller/Plugins/interfaceplugins.h>

class ControllerImage : public AbstractController, public InterfacePlugins {
	Q_OBJECT
	Q_INTERFACES(InterfacePlugins)
	Q_PLUGIN_METADATA(IID "com.chewnonobelix.MediaPlayer.Image")
public:
	ControllerImage() = default;
	ControllerImage(const ControllerImage &) = default;
	~ControllerImage() override = default;

	void exec() override;

	QString playerView() const override;
	QString libraryView() const override;
	void setLibrary(LibraryPointer) override;
	void setMedia(MediaPointer) override;
};
