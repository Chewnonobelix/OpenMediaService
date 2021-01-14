#pragma once

#include "playlist.h"

class SmartPlaylist;

typedef QSharedPointer<SmartPlaylist> SmartPlaylistPointer;

class SmartPlaylist : public PlayList {
	Q_OBJECT

private:
	bool isValid(MediaPointer) const;

public:
	SmartPlaylist() = default;
	using PlayList::PlayList;
	SmartPlaylist(const SmartPlaylist &) = default;
	~SmartPlaylist() = default;

public slots:
	void append(MediaPointer, int = -1) override;
	void onMediaChanged(MediaPointer);
};
