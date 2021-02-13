#include "video_plugin.h"

#include <qqml.h>

void VideoPlugin::registerTypes(const char *) {
	// @uri com.chewnonoeblix.MediaPlayer.Components
	qmlRegisterModule("MediaPlayer.Video", 1, 0);
}
