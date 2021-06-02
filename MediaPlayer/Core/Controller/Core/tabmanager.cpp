#include "tabmanager.h"

void TabManager::Data::setPlaylist(PlaylistPointer pl)
{
    playlist->disconnect(SIGNAL(play(MediaPointer)));
    playlist = pl;

}
void TabManager::addTab()
{
    m_model<<Data{};
    beginInsertRows(QModelIndex(), rowCount() - 1, rowCount()-1);
    insertRows(rowCount()- 1, 1);
    endInsertRows();
    emit clicked(m_model.last().id.toString());
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
    case TabRole::PlayerRole:
        return QVariant::fromValue(m_model[row].player);
    case TabRole::PlaylistRole:
        return QVariant::fromValue(m_model[row].playlist.data());
    case TabRole::DataRole:
        return QVariant::fromValue(m_model[row]);
    }

    return QVariant();
}

int TabManager::rowCount(const QModelIndex &) const { return m_model.size(); }

QHash<int, QByteArray> TabManager::roleNames() const {
    static QHash<int, QByteArray> ret {{int(TabRole::PlayerRole), "player"},
                                       {int(TabRole::IdRole), "id"},
                                       {int(TabRole::DataRole), "data"},
                                       {int(TabRole::PlaylistRole), "playlist"}};
    return ret;
}

bool TabManager::removeTab(QUuid)
{
    return false;
}

bool TabManager::moveTab(QUuid, int)
{
    return false;
}

bool TabManager::contains(QUuid id) const
{
    auto it = std::find_if(m_model.begin(), m_model.end(), [id](Data d) {
            return id == d.id;
    });

    return it != m_model.end();
}

TabManager::Data& TabManager::operator[](QUuid id)
{
    auto it = std::find_if(m_model.begin(), m_model.end(), [id](Data d) {
            return id == d.id;
    });

    return *it;
}

QUuid TabManager::id() const
{
    return m_id;
}

int TabManager::indexOf(QUuid id) const
{
    auto ret = -1;
    for(auto i = 0; i < m_model.size(); i++)
        if(m_model[i].id == id)
            ret = i;

    return ret;

}
