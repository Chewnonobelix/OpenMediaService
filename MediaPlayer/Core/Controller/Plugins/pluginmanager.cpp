#include "pluginmanager.h"

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
    if(m_plugins.contains(role))
        return m_plugins[role];

    return QSharedPointer<InterfacePlugins>();
}

QVariant PluginManager::data(const QModelIndex & index , int role) const
{

    return QVariant();
}

QHash<int, QByteArray> PluginManager::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(PluginRole::NameRole), "name"},
                                         {int(PluginRole::EnableRole), "enable"}};

    return ret;
}

int PluginManager::rowCount(QModelIndex const&) const
{
    return m_plugins.size();
}
