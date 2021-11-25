#pragma once

#include <QAbstractListModel>
#include <QImage>

#include <Model/media.h>
#include <Model/playlist.h>

class ComicsPlaylist: public QAbstractListModel
{
    Q_OBJECT

    struct Stack {
        QString name;
        QList<MediaPointer> medias;
        QImage mini;
    };

    enum class PlaylistRole{NameRole = Qt::UserRole + 1};

private:
    QMap<QString, Stack> m_stacks;
    QString m_currentStackIndex;

public:
    ComicsPlaylist(QObject* = nullptr);
    void init(PlaylistPointer);

    int rowCount(const QModelIndex& = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex&, int = Qt::UserRole) const override;
};

