#pragma once

#include <QAbstractListModel>
#include <QUuid>

#include <Model/global.h>

class TagModel : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(TagModel)

    enum class TagRole {TagRole = Qt::UserRole + 1, UidRole};

public:
    explicit TagModel(QObject *parent = nullptr);
    ~TagModel() override = default;

    Q_INVOKABLE QString addTag(QString);
    Q_INVOKABLE bool editTag(QUuid, QString);
    Q_INVOKABLE bool removeTag(QUuid);
    void setModel(QList<MediaPlayerGlobal::Tag>);

public:
    // Basic functionality:
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &, int = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<MediaPlayerGlobal::Tag> m_model;

signals:
    void s_addTag(MediaPlayerGlobal::Tag);
    void s_editTag(MediaPlayerGlobal::Tag);
    void s_removeTag(MediaPlayerGlobal::Tag);
};

