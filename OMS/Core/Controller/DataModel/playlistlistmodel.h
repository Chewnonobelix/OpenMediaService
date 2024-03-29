#pragma once

#include <QAbstractTableModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <Controller/Core/abstractcontroller.h>

#include <mediaplayercore_global.h>

#include "Model/playlist.h"

class MEDIAPLAYERCORE_EXPORT PlaylistListModel: public QAbstractTableModel
{
    Q_OBJECT
    Q_DISABLE_COPY(PlaylistListModel)

    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)

private:
    enum class ListRole{DisplayRole = Qt::UserRole +1, IndexRole, OrderRole, PointerRole};
    enum class TristateOrder{NoOrder, AscendingOrder, DescendingOrder};

    struct Column {
        QString display;
        QString name;
        MediaPlayerGlobal::Type type = MediaPlayerGlobal::Type::String;
        TristateOrder order = TristateOrder::NoOrder;
        bool enable = true;
        int width = -1;
    };

    QList<MediaPlayerGlobal::Tag> m_tags;
    PlaylistPointer m_model;
    QList<int> m_sortList;
    QList<Column> m_columns;
    int m_width = 0;

    Q_INVOKABLE TristateOrder nextOrder(TristateOrder);

    int width() const;
    void setWidth(int);

public:
    PlaylistListModel() = default;

    void setPlaylist(PlaylistPointer);
    Q_INVOKABLE QStringList columnModel() const;

    Q_INVOKABLE void play(int);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;

    QVariant data(const QModelIndex&, int) const override;
    bool setData(const QModelIndex &, const QVariant &, int role = Qt::EditRole) override;
    Q_INVOKABLE void sort(int);

    QHash<int, QByteArray> roleNames() const override;

    void initColumn(QJsonDocument);
    Q_INVOKABLE int columnOf(QString) const;
    Q_INVOKABLE QStringList columnList() const;
    Q_INVOKABLE bool columnEnable(QString) const;
    Q_INVOKABLE bool setColumnEnable(QString, bool);
    bool resizeColumn();
    Q_INVOKABLE int columnWidth(int) const;
    Q_INVOKABLE void setColumnWidth(int, int);
    void setTags(QList<MediaPlayerGlobal::Tag>);

    Q_INVOKABLE void displayProperties(int);
    Q_INVOKABLE Media* mediaAt(int);

signals:
    void widthChanged();
};

