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

    auto toString = [](auto r) {
        switch(r) {
        case MediaRole::Audio:
            return "Audio";
        case MediaRole::Video:
            return "Video";
        case MediaRole::Books:
            return "Books";
        case MediaRole::Comics:
            return "Comics";
        case MediaRole::Image:
            return "Image";
        case MediaRole::Game:
            return "Game";
        default:
            return "Undefined";
        }
    };

    if(index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    auto row = index.row();
    auto erole = PluginRole(role);

    switch(erole) {
    case PluginRole::EnableRole:
        return false;
    case PluginRole::NameRole:
        return toString(m_plugins.keys()[row]);

    }

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
