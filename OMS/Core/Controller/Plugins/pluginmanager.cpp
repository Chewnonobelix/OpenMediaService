#include "pluginmanager.h"
#include <Controller/Core/abstractcontroller.h>

void PluginManager::init() {
    QDir dir;
    dir.cd("Plugins");
    auto list = dir.entryInfoList({"*.dll"});

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

    for (auto it : list) {
        QPluginLoader loader(it.absoluteFilePath());
        auto obj = dynamic_cast<InterfacePlugins *>(loader.instance());
        QSharedPointer<InterfacePlugins> p(obj);

        if(p){
            m_plugins[p->role()] = {p, true};

            m_liste << Plugin {toString(p->role()), p->role(), p, AbstractController::s_settings->plugin(toString(p->role()))};
        }
    }
}

QSharedPointer<InterfacePlugins>
PluginManager::operator[](MediaRole role) const {
    if(m_plugins.contains(role))
        return m_plugins[role].first;

    return QSharedPointer<InterfacePlugins>();
}

QVariant PluginManager::data(const QModelIndex & index , int role) const
{
    if(index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    auto row = index.row();
    auto erole = PluginRole(role);

    switch(erole) {
    case PluginRole::EnableRole:
        return m_liste[row].enable;
    case PluginRole::NameRole:
        return m_liste[row].name;
    case PluginRole::RoleRole:
        return QVariant::fromValue(m_liste[row].role);
    case PluginRole::SettingsViewRole:
        return m_liste[row].plugin->settingsView();
    }

    return QVariant();
}

QHash<int, QByteArray> PluginManager::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(PluginRole::NameRole), "name"},
                                         {int(PluginRole::RoleRole), "role"},
                                         {int(PluginRole::SettingsViewRole), "settingsView"},
                                         {int(PluginRole::EnableRole), "enable"}};

    return ret;
}

int PluginManager::rowCount(QModelIndex const&) const
{
    return m_liste.size();
}

bool PluginManager::setData(const QModelIndex& index, const QVariant& data, int role)
{
    m_liste[index.row()].enable = data.toBool();
    emit dataChanged(index, index, {role});
    return true;
}

QStringList PluginManager::pluginsName() const
{
    QStringList ret;
    for(auto it: m_liste) {
        ret<<it.name;
    }

    return ret;
}

MediaRole PluginManager::pluginRole(QString name) const
{
    MediaRole ret = MediaRole::Undefined;
    std::for_each(m_liste.begin(), m_liste.end(), [&ret, name](auto it) {
        if(name == it.name)
            ret = it.role;
    });

    return ret;
}

bool PluginManager::pluginEnable(QString name) const
{
    bool ret = false;
    std::for_each(m_liste.begin(), m_liste.end(), [&ret, name](auto it) {
        if(name == it.name)
            ret = it.enable;
    });

    return ret;
}
