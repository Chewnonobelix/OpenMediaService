#include "tabmanager.h"

QUuid TabManager::s_currentTab = QUuid();
QList<TabManager::Data>::iterator TabManager::s_current = QList<Data>::iterator();
QList<TabManager*> TabManager::s_list = QList<TabManager*>();

void TabManager::addTab()
{
    m_model<<Data{};
    beginInsertRows(QModelIndex(), rowCount() - 1, rowCount()-1);
    insertRows(rowCount()- 1, 1);
    endInsertRows();
    s_list<<this;
}

QVariant TabManager::data(const QModelIndex &index, int role) const {
    auto row = index.row();
    if(row < 0 || row >= rowCount())
        return QVariant();

    auto roleEnum = TabRole(role);

    switch(roleEnum)
    {
    case TabRole::IdRole:
        return m_model[row].id;
    case TabRole::LibRole:
        return m_model[row].libIndex;
    case TabRole::PlaylistRole:
        return m_model[row].playlistIndex;
    case TabRole::IsCurrentRole:
        return m_model[row].id == s_currentTab;
    }

    return QVariant();
}

int TabManager::rowCount(const QModelIndex &) const { return m_model.size(); }

QHash<int, QByteArray> TabManager::roleNames() const {
    static QHash<int, QByteArray> ret {{int(TabRole::LibRole), "library"},
                                       {int(TabRole::IdRole), "id"},
                                       {int(TabRole::IsCurrentRole), "isCurrentTab"},
                                       {int(TabRole::PlaylistRole), "playlist"}};
    return ret;
}

bool TabManager::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug()<<"Set"<<index<<value<<role;
    auto erole = TabRole(role);

    switch(erole)
    {
    case TabRole::LibRole:
        m_model[index.row()].libIndex = value.toInt();
        break;
    case TabRole::PlaylistRole:
        m_model[index.row()].playlistIndex = value.toInt();
        break;
    default:
        break;
    }

    emit dataChanged(index, index, {role});
    return true;
}

void TabManager::setCurrentTab(QString id)
{
    s_currentTab = QUuid::fromString(id);

    s_current = std::find_if(m_model.begin(), m_model.end(), [id](const auto& it) {
        return it.id.toString() == id;
    });

}

QUuid TabManager::currentTabId()
{
    return s_currentTab;
}

QVariant TabManager::at(int index, QString role) const
{
    if(index < 0 || index > rowCount())
        return QVariant();


   if(role == "library")
       return m_model[index].libIndex;
   if(role == "playlist")
       return m_model[index].playlistIndex;

    return QVariant();
}

void TabManager::setCurrentLibrary(int lib)
{
    if(s_current != m_model.end())
        s_current->libIndex = lib;
}

void TabManager::setCurrentPlaylist(int pl)
{
    if(s_current != m_model.end())
        s_current->playlistIndex = pl;
}

void TabManager::setGlobalCurrentLibrary(int lib)
{
    for(auto it: s_list)
        it->setCurrentLibrary(lib);
}

void TabManager::setGlobalCurrentPlaylist(int pl)
{
    for(auto it: s_list)
        it->setCurrentPlaylist(pl);
}
