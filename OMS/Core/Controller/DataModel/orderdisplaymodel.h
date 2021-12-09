#pragma once

#include <QAbstractListModel>

#include <mediaplayercore_global.h>

#include <Model/playlist.h>

class MEDIAPLAYERCORE_EXPORT OrderDisplayModel: public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(OrderDisplayModel)

private:
    enum class OrderRole{DisplayRole = Qt::UserRole + 1, IndexRole, CurrentIndexRole};
    PlaylistPointer m_playlist;

public:
    OrderDisplayModel(QObject* = nullptr);
    ~OrderDisplayModel() = default;


    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setPlaylist(PlaylistPointer);
};

