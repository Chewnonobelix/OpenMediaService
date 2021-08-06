#include "playlistlistmodel.h"

void PlaylistListModel::setPlaylist(PlaylistPointer p)
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    removeRows(0, rowCount());
    endRemoveRows();
    beginRemoveColumns(QModelIndex(), 0, columnCount());
    removeColumns(0, columnCount());
    endRemoveColumns();

    m_model = p;

    for(auto& it: m_columns) {
        it.enable = AbstractController::s_settings->playlistColumn(p->id().toString(), it.name);
    }


    beginInsertRows(QModelIndex(), 0, rowCount());
    insertRows(0, rowCount());
    endInsertRows();
    beginInsertColumns(QModelIndex(), 0, columnCount());
    insertColumns(0, columnCount());
    endInsertColumns();

    m_sortList.clear();
    if(p)
        for(auto it = 0; it < p->count(); it++)
            m_sortList<<it;

    sort(0);

}

int PlaylistListModel::rowCount(const QModelIndex&) const
{
    return m_sortList.size();
}

int PlaylistListModel::columnCount(const QModelIndex&) const {
    auto ret = 0;
    for(auto it: m_columns)
        if(it.enable) {
            ret ++;
        }

    return ret;
}

QVariant PlaylistListModel::data(const QModelIndex& index, int role) const {
    auto row = index.row(), col = index.column();

    if((row < 0 || row >= rowCount()) || (col < 0 || col >= columnCount()))
        return QVariant();

    auto current = (*m_model)[m_sortList[row]];
    auto colDisplay = columnModel()[col];
    auto currentCol = *(std::find_if(m_columns.begin(), m_columns.end(), [colDisplay](Column it) {
        return it.display == colDisplay;
    }));

    switch(ListRole(role)) {
    case ListRole::DisplayRole:
        if(currentCol.name == "file") {
            return current->path().split("/").last();
        }
        else if(currentCol.name == "ext") {
            auto last = current->path().lastIndexOf(".");
            return current->path().mid(last);
        }
        else if(currentCol.type == MediaPlayerGlobal::Type::StringContainer) {
            return current->metaData<QStringList>(currentCol.name);
        }
        else {
            return current->metaData<QVariant>(currentCol.name);
        }

    case ListRole::IndexRole:
        return m_model->indexOf(current);
        break;
    case ListRole::OrderRole:
        return QVariant::fromValue(currentCol.order);
        break;
    default:
        break;
    }
    return QVariant();
}

void PlaylistListModel::sort(int col) {

    auto order = m_columns[col].order;

    for(auto& it: m_columns)
        it.order = TristateOrder::NoOrder;

    m_columns[col].order = nextOrder(order);

    for(auto i = 0; i < m_sortList.count(); i ++)
    {
        auto mi = (*m_model)[m_sortList[i]];
        for(auto j = i; j < m_sortList.count(); j++) {
            auto mj = (*m_model)[m_sortList[j]];

            switch (m_columns[col].order) {
            case TristateOrder::AscendingOrder:
                if(compare(mi, mj, m_columns[col].name) != Media::CompareState::SuperiorState)
                {
                    m_sortList.swapItemsAt(i, j);
                    mi = mj;
                }
                break;
            case TristateOrder::DescendingOrder:
                if(compare(mi, mj, m_columns[col].name) != Media::CompareState::InferiorState)
                {
                    m_sortList.swapItemsAt(i, j);
                    mi = mj;
                }
                break;
            default:
                if(m_sortList[j] < m_sortList[i]){
                    m_sortList.swapItemsAt(i, j);
                    mi = mj;
                }
                break;
            }
        }
    }
    beginRemoveRows(QModelIndex(), 0, rowCount());
    removeRows(0, rowCount());
    endRemoveRows();
    beginInsertRows(QModelIndex(), 0, rowCount());
    insertRows(0, rowCount());
    endInsertRows();
}

QHash<int, QByteArray> PlaylistListModel::roleNames() const
{
    static QHash<int, QByteArray> ret = {{int(ListRole::DisplayRole), "display"},
                                         {int(ListRole::OrderRole), "order"},
                                         {int(ListRole::IndexRole), "index"}
                                        };
    return ret;
}

QStringList PlaylistListModel::columnModel() const {
    QStringList ret;
    for(auto it: m_columns)
        if(it.enable)
            ret<<it.display;

    return ret;
}

QVariant PlaylistListModel::headerData(int section, Qt::Orientation, int) const
{
    return columnModel()[section];
}

void PlaylistListModel::play(int index)
{
    QList<int> read;
    for(auto it = 0; it < m_model->count(); it++)
        read<<it;

    if(m_model->isShuffle())
    {
        QRandomGenerator generator;
        read.swapItemsAt(0, read.indexOf(index));
        for(auto i = 1; i < read.size(); i++) {
            auto r = generator.bounded(i, int(read.count()));
            read.swapItemsAt(i, r);
        }
    }
    else
    {
        for(auto i = 0; i < index; i++) {
            read.takeFirst();
        }
    }

    m_model->setReadOrder(read);
    m_model->setCurrentIndex(index-1);
    m_model->next();
}

PlaylistListModel::TristateOrder PlaylistListModel::nextOrder(TristateOrder order) {
    switch (order) {
    case TristateOrder::NoOrder:
        return TristateOrder::AscendingOrder;
    case TristateOrder::AscendingOrder:
        return TristateOrder::DescendingOrder;
    case TristateOrder::DescendingOrder:
        return TristateOrder::NoOrder;
    }

    return TristateOrder::NoOrder;
}

bool PlaylistListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(m_columns[index.column()].name == "rating")
        (*m_model)[m_sortList[index.row()]]->setRating(value.toInt());
    emit dataChanged(index, index, {role});
    return true;
}

int PlaylistListModel::columnOf(QString name) const
{
    auto ret = m_columns.size();
    for(auto it = 0; it < m_columns.count(); it++) {
        if(m_columns[it].name == name)
            ret = it;
    }

    return ret;
}

void PlaylistListModel::initColumn(QJsonDocument obj)
{
    auto array = obj.array();

    m_columns << Column{"File", "file"}<< Column {"Ext", "ext"};
    for(auto it: array) {
        auto iobj = it.toObject();
        Column c {iobj["display"].toString(), iobj["name"].toString(), iobj["type"].toVariant().value<MediaPlayerGlobal::Type>(),
                 TristateOrder::NoOrder, true};
        m_columns<<c;
    }
}

QStringList PlaylistListModel::columnList() const
{
    QStringList ret;
    for(auto it: m_columns)
        ret<<it.display;

    return ret;
}

bool PlaylistListModel::columnEnable(QString display) const
{
    for(auto it: m_columns)
        if(it.display == display)
            return it.enable;

    return false;
}

bool PlaylistListModel::setColumnEnable(QString display, bool enable)
{
    for(auto& it: m_columns)
        if(it.display == display) {
            it.enable = enable;
            AbstractController::s_settings->setPlaylistColumn(m_model->id().toString(),
                                                              it.name, enable);
            resizeColumn();
            return true;
        }

    return false;
}

bool PlaylistListModel::resizeColumn()
{
    beginRemoveColumns(QModelIndex(), 0, m_columns.size());
    removeColumns(0, m_columns.size());
    endRemoveColumns();

    beginInsertColumns(QModelIndex(), 0, columnCount());
    insertColumns(0, columnCount());
    endInsertColumns();

    return true;
}

int PlaylistListModel::columnWidth(int) const
{
    return columnCount() > 0 ? width() / columnCount() : 0;
}

int PlaylistListModel::width() const
{
    return m_width;
}

void PlaylistListModel::setWidth(int w)
{
    m_width = w;
    emit widthChanged();
}
