#pragma once

#include <QAbstractListModel>
#include <QImage>

#include <Model/media.h>
#include <Model/playlist.h>
#include "comicsmedia.h"

class ComicsPlaylist: public QAbstractListModel
{
    Q_OBJECT

    struct Stack {
        QString name;
        QList<Media*> medias;
        QImage mini;
    };

    enum class PlaylistRole{NameRole = Qt::UserRole + 1, ListRole, CoverRole};
    PlaylistPointer m_current;

private:
    QMap<QString, Stack> m_stacks;
    QString m_currentStackIndex;
    bool m_split = false;

public:
    ComicsPlaylist(QObject* = nullptr);
    void init(PlaylistPointer p, QList<ComicsMedia>);
    void setSplit(bool);
    bool split() const;

    Q_INVOKABLE void play(Media*);

    int rowCount(const QModelIndex& = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex&, int = Qt::UserRole) const override;
};

