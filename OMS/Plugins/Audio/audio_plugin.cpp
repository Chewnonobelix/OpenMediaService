#include "audio_plugin.h"

#include <qqml.h>

void AudioPlugin::registerTypes(const char *) {
	// @uri com.chewnonoeblix.MediaPlayer.Components
    qmlRegisterModule("MediaPlayer.Audio", 1, 0);
}
