#include "image_plugin.h"

#include <qqml.h>

void ImagePlugin::registerTypes(const char *) {
	// @uri com.chewnonoeblix.MediaPlayer.Components
	qmlRegisterModule("MediaPlayer.Image", 1, 0);
}
