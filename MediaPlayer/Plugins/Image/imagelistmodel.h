#pragma once

#include <QAbstractTableModel>

#include "Model/playlist.h"

class ImageListModel: public QAbstractTableModel
{
    Q_OBJECT
    Q_DISABLE_COPY(ImageListModel)

private:
    enum class ImageListRole{DisplayRole = Qt::UserRole +1, RatingRole, FileRole, ExtensionRole, PathRole, CountRole, AddedRole, LastPlayRole, Fullpath, IndexRole, OrderRole};
    enum class TristateOrder{NoOrder, AscendingOrder, DescendingOrder};

    struct Column {
        QString display;
        QString name;
        ImageListRole role;
        TristateOrder order;
    };

    PlaylistPointer m_model;
    QList<int> m_sortList;
    QList<Column> m_columns = {{"File", "file", ImageListRole::FileRole, TristateOrder::NoOrder},
                               {"Path", "path", ImageListRole::PathRole, TristateOrder::NoOrder},
                               {"Count", "count", ImageListRole::CountRole, TristateOrder::NoOrder},
                               {"Added", "added", ImageListRole::AddedRole, TristateOrder::NoOrder},
                               {"Last play", "lastPlayed", ImageListRole::LastPlayRole, TristateOrder::NoOrder},
                               {"Rating", "rating", ImageListRole::RatingRole, TristateOrder::NoOrder},
                               {"Ext", "ext", ImageListRole::ExtensionRole, TristateOrder::NoOrder}};

    Q_INVOKABLE TristateOrder nextOrder(TristateOrder);

public:
    ImageListModel() = default;

    void setPLaylist(PlaylistPointer);
    Q_INVOKABLE QStringList columnModel() const;

    Q_INVOKABLE void play(int);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;

    QVariant data(const QModelIndex&, int) const override;
    bool setData(const QModelIndex &, const QVariant &, int role = Qt::EditRole) override;
    Q_INVOKABLE void sort(int, TristateOrder order = TristateOrder::NoOrder);

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE int columnOf(QString) const;
};

