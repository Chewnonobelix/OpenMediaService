#include "UxComponent_plugin.hpp"

#include <qqml.h>

void UxComponentPlugin::registerTypes(const char *) {
	// @uri com.chewnonoeblix.MediaPlayer.Components
	qmlRegisterModule("MediaPlayer.Components", 1, 0);
}
