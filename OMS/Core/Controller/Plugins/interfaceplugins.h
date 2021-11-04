#pragma once

#include <QObject>
#include <QQmlComponent>

#include <mediaplayercore_global.h>

#include "interfaceimporter.h"
#include <Model/library.h>
#include <Model/media.h>

class MEDIAPLAYERCORE_EXPORT InterfacePlugins {
private:
    QUuid m_tabId;

public:
	InterfacePlugins() = default;
	InterfacePlugins(const InterfacePlugins &) = default;
	virtual ~InterfacePlugins() = default;

    virtual QObject* playerView() const = 0;
    virtual QObject *playlistView() = 0;
    virtual QUrl settingsView() const = 0;

	virtual void setPlaylist(PlaylistPointer) = 0;
	virtual void setMedia(MediaPointer) = 0;

	virtual MediaRole role() const = 0;
	virtual QStringList filters() const = 0;
    virtual QString rules() const = 0;
    virtual QList<QSharedPointer<InterfaceImporter>> importers () const = 0;
	virtual void exec() = 0;
	virtual QSharedPointer<InterfacePlugins> clone() const = 0;

    QUuid id() const;
    void setID(QUuid);
};

Q_DECLARE_INTERFACE(InterfacePlugins, "InterfacePlugins/1.0")
