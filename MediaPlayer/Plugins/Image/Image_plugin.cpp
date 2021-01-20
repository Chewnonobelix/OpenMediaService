#include "Image_plugin.hpp"

#include <qqml.h>

void ImagePlugin::registerTypes(const char *) {
	// @uri com.chewnonoeblix.MediaPlayer.Components
	qmlRegisterModule("MediaPlayer.Image", 1, 0);
}
