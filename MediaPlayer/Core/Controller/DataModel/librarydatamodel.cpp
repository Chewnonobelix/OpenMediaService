#include "librarydatamodel.h"

LibraryDataModel::LibraryDataModel(const LibraryDataModel &l)
    : QAbstractListModel(), m_libraries(l.m_libraries)
{
    sort(0, Qt::AscendingOrder);
}

int LibraryDataModel::rowCount(const QModelIndex &) const
{
    return m_libraries.size();
}

QVariant LibraryDataModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_libraries.count())
        return QVariant();

    auto lib = m_libraries[index.row()];

    if (role == MediaRole)
        return QVariant::fromValue(lib->role());
    else if (role == NameRole)
        return lib->name();
    else if (role == IndexRole)
        return index.row();

    return QVariant::fromValue(lib.data());
}

QHash<int, QByteArray> LibraryDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[MediaRole] = "role";
    roles[NameRole] = "name";
    roles[IndexRole] = "index";
    return roles;
}

void LibraryDataModel::insertData(LibraryPointer l)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_libraries << l;
    endInsertRows();
}

Library *LibraryDataModel::at(int index)
{
    if (index >= rowCount())
        return nullptr;

    return m_libraries[index].data();
}

void LibraryDataModel::sort(int, Qt::SortOrder order)
{
    auto l = m_libraries;

    std::sort(l.begin(), l.end(), [order](LibraryPointer l1, LibraryPointer l2) {
        if (order == Qt::DescendingOrder) {
            return !(l1 < l2);
        } else {
            return l1 < l2;
        }
    });

    clear();
    for (auto it : l)
        insertData(it);
}

void LibraryDataModel::clear()
{
    qDebug() << "Clear" << rowCount();
    removeRows(0, rowCount());
    m_libraries.clear();
    qDebug() << rowCount();
}

LibraryDataModel &LibraryDataModel::operator=(const LibraryDataModel &ldm)
{
    for (auto it : ldm.m_libraries)
        insertData(it);
    m_currentIndex = ldm.m_currentIndex;

    return *this;
}

bool operator!=(const LibraryDataModel &l1, const LibraryDataModel &l2)
{
    return l1.m_libraries != l2.m_libraries;
}
