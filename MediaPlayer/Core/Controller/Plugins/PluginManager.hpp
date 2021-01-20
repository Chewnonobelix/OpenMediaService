#pragma once

#include <QMap>
#include <QPluginLoader>

#include "interfaceplugins.h"
#include <Model/global.h>

class PluginManager {
private:
	QMap<MediaRole, QSharedPointer<InterfacePlugins>> m_plugins;

public:
	PluginManager() = default;
	PluginManager(const PluginManager &) = default;
	~PluginManager() = default;

	void init();

	QSharedPointer<InterfacePlugins> operator[](MediaRole) const;
};
