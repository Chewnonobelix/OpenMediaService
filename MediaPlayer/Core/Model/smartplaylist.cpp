#include "smartplaylist.h"

bool SmartPlaylist::isValid(MediaPointer) const { return true; }

void SmartPlaylist::append(MediaPointer m, int p) {
	if (isValid(m))
		PlayList::append(m, p);
}

void SmartPlaylist::onMediaChanged(MediaPointer m) {
	if (!m.isNull())
		append(m);
}
