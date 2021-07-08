#include "playlistmodel.h"
//#include <Controller/Core/controllerlibrary.h>

PlaylistModel::PlaylistModel(const PlaylistModel &) : QAbstractListModel() {}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
    if (index.row() >= rowCount() || index.row() < 0)
        return QVariant();

    int i = index.row();

    auto p = (*this)[i];
    switch (PlaylistRole(role)) {
    case PlaylistRole::NameRole:
        return p->name();
        break;
    case PlaylistRole::SmartRole:
        return i < m_smarts.size();
        break;

    case PlaylistRole::IdRole:
        return p->id();

        break;
    }

    return QVariant();
}

int PlaylistModel::rowCount(const QModelIndex &) const {
    return m_smarts.size() + m_normals.size();
}

QHash<int, QByteArray> PlaylistModel::roleNames() const {
    static QHash<int, QByteArray> ret{{int(PlaylistRole::NameRole), "name"},
                                      {int(PlaylistRole::SmartRole), "smart"},
                                      {int(PlaylistRole::IdRole), "id"}};
    return ret;
}

void PlaylistModel::sort(int, Qt::SortOrder) {}

void PlaylistModel::setSmart(QList<SmartPlaylistPointer> s) {
    for(auto it: m_smarts)
        it->disconnect(SIGNAL(nameChanged()));

    beginRemoveRows(QModelIndex(), 0, m_smarts.size() - 1);
    removeRows(0, m_smarts.size() - 1);
    endRemoveRows();

    m_smarts.clear();
    m_smarts = s;

    beginInsertRows(QModelIndex(), 0, m_smarts.size() - 1);
    insertRows(0, m_smarts.size() - 1);
    endInsertRows();

    for(auto it: m_smarts)
        connect(it.data(), &PlayList::nameChanged, this, &PlaylistModel::onPlaylistNameChanged);

}

void PlaylistModel::setNormal(QList<PlaylistPointer> n) {
    for(auto it: m_normals)
        it->disconnect(SIGNAL(nameChanged()));

    beginRemoveRows(QModelIndex(), m_smarts.size() - 1, m_normals.size() - 1);
    removeRows(m_smarts.size() - 1, m_normals.size() - 1);
    endRemoveRows();

    m_normals.clear();
    m_normals = n;

    beginInsertRows(QModelIndex(), m_smarts.size() - 1, m_normals.size() - 1);
    insertRows(m_smarts.size() - 1, m_normals.size() - 1);
    endInsertRows();

    for(auto it: m_normals)
        connect(it.data(), &PlayList::nameChanged, this, &PlaylistModel::onPlaylistNameChanged);
}

int PlaylistModel::currentIndex() const { return m_currentIndex; }

void PlaylistModel::setCurrentIndex(int index) {
    m_currentIndex = index;
    emit currentIndexChanged();
}

PlaylistPointer PlaylistModel::current() const {
    if (m_currentIndex == -1)
        return PlaylistPointer();

    return m_currentIndex < m_smarts.size()
            ? m_smarts[m_currentIndex]
              : m_normals[m_currentIndex - m_smarts.size()];
}

void PlaylistModel::onLibraryChanged(LibraryPointer l) {
    if (l.isNull())
        return;

    auto index = currentIndex();
    setSmart(l->smartPlaylist().values());
    setNormal(l->playlist().values());
    setCurrentIndex(index);
}

PlaylistPointer PlaylistModel::operator[](int index) const {
    return index < m_smarts.size() ? m_smarts[index]
                                     : m_normals[index - m_smarts.size()];
}

void PlaylistModel::editPlaylist()
{
    auto context = new QQmlContext(AbstractController::engine()->qmlEngine().rootContext());
    context->setContextProperty("_playlist", current().data());
    context->setContextProperty("_smart", !current().dynamicCast<SmartPlaylist>().isNull());
    context->setContextProperty("_smartModel", &m_smartModel);

    if(!current().dynamicCast<SmartPlaylist>().isNull())
        m_smartModel.setModel(current().dynamicCast<SmartPlaylist>()->rules());
    qDebug() << "Playlist context";
    AbstractController::engine()->createWindow(QUrl(QStringLiteral("/PlaylistView.qml")), context);
}

void PlaylistModel::onPlaylistNameChanged()
{
    auto pl = dynamic_cast<PlayList*>(sender());
    int i = 0;

    QModelIndex ind;
    for(; i < m_smarts.size() && !ind.isValid(); i++)
    {
        if(pl->name() == m_smarts[i]->name())
            ind = index(i);
    }

    for(; i < (m_normals.size() + m_smarts.size()) && !ind.isValid(); i++)
    {
        if(pl->name() == m_normals[i - m_smarts.size()]->name())
            ind = index(i);
    }

    emit dataChanged(ind, ind, {int(PlaylistRole::NameRole)});
}
