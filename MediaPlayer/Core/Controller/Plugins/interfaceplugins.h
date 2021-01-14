#pragma once

#include <QObject>

#include <mediaplayercore_global.h>

#include <Model/library.h>
#include <Model/media.h>

class MEDIAPLAYERCORE_EXPORT InterfacePlugins {
public:
	InterfacePlugins() = default;
	InterfacePlugins(const InterfacePlugins &) = default;
	virtual ~InterfacePlugins() = default;

	virtual QString playerView() const = 0;
	virtual QString libraryView() const = 0;
	virtual void setLibrary(LibraryPointer) = 0;
	virtual void setMedia(MediaPointer) = 0;
};

Q_DECLARE_INTERFACE(InterfacePlugins, "InterfacePlugins/1.0")
