#pragma once

#include <QObject>
#include <QQmlComponent>

#include <mediaplayercore_global.h>

#include <Model/library.h>
#include <Model/media.h>

class MEDIAPLAYERCORE_EXPORT InterfacePlugins {
public:
	InterfacePlugins() = default;
	InterfacePlugins(const InterfacePlugins &) = default;
	virtual ~InterfacePlugins() = default;

	virtual QString playerView() const = 0;
	virtual QQmlComponent *playlistView() = 0;
	virtual void setPlaylist(PlaylistPointer) = 0;
	virtual void setMedia(MediaPointer) = 0;

	virtual MediaRole role() const = 0;
	virtual QStringList filters() const = 0;

	virtual void exec() = 0;
	virtual QSharedPointer<InterfacePlugins> clone() const = 0;
};

Q_DECLARE_INTERFACE(InterfacePlugins, "InterfacePlugins/1.0")
