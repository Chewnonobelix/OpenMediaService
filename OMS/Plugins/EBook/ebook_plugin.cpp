#include "ebook_plugin.h"

#include <qqml.h>

void EBookPlugin::registerTypes(const char *) {
	// @uri com.chewnonoeblix.MediaPlayer.Components
    qmlRegisterModule("MediaPlayer.EBook", 1, 0);
}
