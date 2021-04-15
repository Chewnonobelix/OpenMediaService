#pragma once

#include <QAbstractTableModel>

#include "Model/playlist.h"

class ImageListModel: public QAbstractTableModel
{
    Q_OBJECT
    Q_DISABLE_COPY(ImageListModel)

private:
    enum class ImageListRole{DisplayRole = Qt::UserRole +1};

    PlaylistPointer m_model;

public:
    ImageListModel() = default;

    void setPLaylist(PlaylistPointer);

    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;

    QVariant data(const QModelIndex&, int) const override;
    void sort(int , Qt::SortOrder) override;

    QHash<int, QByteArray> roleNames() const override;
};

