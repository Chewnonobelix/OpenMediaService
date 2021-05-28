#pragma once

#include <QList>
#include <QQueue>
#include <QRandomGenerator>
#include <QSharedPointer>
#include <QUuid>
#include <QVariant>

#include <mediaplayercore_global.h>

#include "global.h"
#include "media.h"

class PlayList;

typedef QSharedPointer<PlayList> PlaylistPointer;

class MEDIAPLAYERCORE_EXPORT PlayList : public QObject,
        public MetaData,
        private QList<MediaPointer> {
    Q_OBJECT

    Q_PROPERTY(QUuid id READ id CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(
            bool isShuffle READ isShuffle WRITE setShuffle NOTIFY isShuffleChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY
               currentIndexChanged)

private:
    QList<int> m_readOrder;
    int m_currentIndex = -1;

public:
    PlayList() = default;
    using MetaData::MetaData;
    PlayList(const PlayList &);
    ~PlayList() = default;

    PlayList &operator=(const PlayList &);

    using QList<MediaPointer>::count;
    using QList<MediaPointer>::isEmpty;
    using QList<MediaPointer>::operator[];
    using QList<MediaPointer>::indexOf;

    QUuid id() const;
    void setId(QUuid);
    QString name() const;
    void setName(QString);
    bool isShuffle() const;
    void setShuffle(bool);
    int currentIndex() const;
    void setCurrentIndex(int);

    //	Q_INVOKABLE void play(int = 0);
    Q_INVOKABLE MediaPointer next();
    Q_INVOKABLE MediaPointer prev();
    void setReadOrder(QList<int>);

signals:
    void nameChanged();
    void countChanged();
    void isShuffleChanged();
    void play(MediaPointer);
    void currentIndexChanged();

public slots:
    Q_INVOKABLE virtual void append(MediaPointer, int = -1);
    Q_INVOKABLE void remove(int);
    Q_INVOKABLE MediaPointer at(int i) const;
    Q_INVOKABLE void swap(int, int);
    Q_INVOKABLE void clear();
};
