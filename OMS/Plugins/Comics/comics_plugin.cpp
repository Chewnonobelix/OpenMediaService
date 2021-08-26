#include "comics_plugin.h"

#include <qqml.h>

void ComicsPlugin::registerTypes(const char *) {
	// @uri com.chewnonoeblix.MediaPlayer.Components
    qmlRegisterModule("MediaPlayer.Comics", 1, 0);
}
