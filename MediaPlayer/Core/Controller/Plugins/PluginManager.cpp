#include "PluginManager.hpp"

void PluginManager::init() {
	QDir dir;
	dir.cd("Plugins");
	auto list = dir.entryInfoList({"*.dll"});

	for (auto it : list) {
		QPluginLoader loader(it.absoluteFilePath());
		auto obj = dynamic_cast<InterfacePlugins *>(loader.instance());
		QSharedPointer<InterfacePlugins> p(obj);

		m_plugins[p->role()] = p;
		p->exec();
	}
}

QSharedPointer<InterfacePlugins>
PluginManager::operator[](MediaRole role) const {
	return m_plugins[role];
}
