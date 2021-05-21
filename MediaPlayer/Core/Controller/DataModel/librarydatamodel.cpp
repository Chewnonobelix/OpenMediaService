#include "librarydatamodel.h"

LibraryDataModel::LibraryDataModel() : QAbstractListModel() {}

LibraryDataModel::LibraryDataModel(const LibraryDataModel &l)
    : QAbstractListModel(), m_libraries(l.m_libraries) {
    sort(0, Qt::AscendingOrder);
}

int LibraryDataModel::rowCount(const QModelIndex &) const {
    return m_libraries.size();
}

QVariant LibraryDataModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_libraries.count())
        return QVariant();

    auto lib = m_libraries[index.row()];

    if (role == MediaRole)
        return QVariant::fromValue(lib.library->role());
    else if (role == NameRole)
        return lib.library->name();
    else if (role == IndexRole)
        return index.row();
    else if (role == IdRole)
        return QVariant::fromValue(lib.library->id());
    else if (role == ControllerRole) {
        return QVariant::fromValue(lib.controller.data());
    }

    return QVariant::fromValue(lib.library.data());
}

QHash<int, QByteArray> LibraryDataModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[MediaRole] = "role";
    roles[NameRole] = "name";
    roles[IndexRole] = "index";
    roles[IdRole] = "id";
    roles[ControllerRole] = "controller";
    return roles;
}

void LibraryDataModel::insertData(LibraryPointer l) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + 1);
    m_libraries << Data{l, new ControllerLibrary};
    QJSEngine::setObjectOwnership(m_libraries.last().controller, QJSEngine::CppOwnership);
    QJSEngine::setObjectOwnership(l.data(), QJSEngine::CppOwnership);

    m_libraries.last().controller->exec();
    m_libraries.last().controller->setCurrentLibrary(l);
    insertRow(rowCount());
    setData(index(rowCount() - 1),
            QVariant::fromValue(m_libraries.last().library.data()));
    endInsertRows();
}

Library *LibraryDataModel::at(int index) {
    if (index >= rowCount() || index < 0)
        return nullptr;

    return m_libraries[index].library.data();
}

ControllerLibrary *LibraryDataModel::controller(int index) {
    if (index >= rowCount() || index < 0)
        return nullptr;

    return m_libraries[index].controller;
}

QQmlComponent *LibraryDataModel::playlistComponent(int index) {
    if (index >= rowCount() || index < 0)
        return nullptr;

    return m_libraries[index].controller->playlistComp(TabManager::currentTabId().toString());
}

void LibraryDataModel::sort(int, Qt::SortOrder order) {
    auto l = m_libraries;

    std::sort(l.begin(), l.end(), [order](auto l1, auto l2) {
        if (order == Qt::DescendingOrder) {
            return !(l1.library < l2.library);
        } else {
            return l1.library < l2.library;
        }
    });

    clear();
    for (auto it : l)
        insertData(it.library);
}

void LibraryDataModel::clear() {
    beginRemoveRows(QModelIndex(), 0, rowCount());
    removeRows(0, rowCount());
    m_libraries.clear();
    endRemoveRows();
}

LibraryDataModel &LibraryDataModel::operator=(const LibraryDataModel &ldm) {
    clear();
    for (auto it : ldm.m_libraries)
        insertData(it.library);
    m_currentIndex = ldm.m_currentIndex;

    return *this;
}


void LibraryDataModel::onUpdateLibraries() {
    clear();
    setCurrentIndex(-1);

    if (!sender())
        return;

    for (auto it : ((InterfaceSaver *)sender())->selectLibrary().values())
        insertData(it);
}

void LibraryDataModel::setCurrentIndex(int index) {
    m_currentIndex = index;
    emit currentIndexChanged();
    TabManager::setGlobalCurrentLibrary(index);

    if(index > -1) {
        auto& ctrl = m_libraries[index].controller;
        ctrl->setPlaylistIndex(TabManager::currentTabId().toString(), 0);
    }
    else
    {
        TabManager::setGlobalCurrentPlaylist(-1);
    }
}

int LibraryDataModel::currentIndex() const { return m_currentIndex; }

int LibraryDataModel::indexOf(LibraryPointer lp) const {
    auto it = std::find_if(m_libraries.begin(), m_libraries.end(), [lp](auto d) {
        return  lp == d.library;
    });

    return std::distance(m_libraries.begin(), it);
}

LibraryPointer LibraryDataModel::operator[](QUuid id) const {
    LibraryPointer ret;

    for (auto it : m_libraries)
        if (it.library->id() == id)
            ret = it.library;

    return ret;
}
