#pragma once

#include <QAbstractTableModel>

#include "Model/playlist.h"

class ImageListModel: public QAbstractTableModel
{
    Q_OBJECT
    Q_DISABLE_COPY(ImageListModel)

private:
    enum class ImageListRole{DisplayRole = Qt::UserRole +1, RatingRole, FileRole, ExtensionRole, PathRole, CountRole, AddedRole, LastPlayRole};

    PlaylistPointer m_model;
    QList<QPair<QString, ImageListRole>> m_columns = {{"File", ImageListRole::FileRole},
                                                     {"Path", ImageListRole::PathRole},
                                                     {"Count", ImageListRole::CountRole},
                                                     {"Added", ImageListRole::AddedRole},
                                                     {"Last play", ImageListRole::LastPlayRole},
                                                     {"Rating", ImageListRole::RatingRole},
                                                     {"Ext", ImageListRole::ExtensionRole}};
public:
    ImageListModel() = default;

    void setPLaylist(PlaylistPointer);

    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;

    QVariant data(const QModelIndex&, int) const override;
    void sort(int , Qt::SortOrder) override;

    QHash<int, QByteArray> roleNames() const override;
};

