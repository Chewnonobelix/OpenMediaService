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
        public QEnableSharedFromThis<PlayList>,
        public QList<MediaPointer> {
    Q_OBJECT

    Q_PROPERTY(QUuid id READ id CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(
            bool isShuffle READ isShuffle WRITE setShuffle NOTIFY isShuffleChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY
               currentIndexChanged)

private:
    int m_currentIndex = -1;

protected:
    QList<int> m_readOrder;

public:
    PlayList() = default;
    using MetaData::MetaData;
    PlayList(const PlayList &);
    PlayList(const QJsonObject&);
    ~PlayList() = default;

    operator QJsonObject() const override;
    PlayList &operator=(const PlayList &);

    using QList<MediaPointer>::count;
    using QList<MediaPointer>::isEmpty;
    using QList<MediaPointer>::operator[];
    using QList<MediaPointer>::indexOf;
    using QList<MediaPointer>::contains;

    QUuid id() const;
    bool setId(QUuid);
    QString name() const;
    bool setName(QString);
    bool isShuffle() const;
    bool setShuffle(bool);
    int currentIndex() const;
    bool setCurrentIndex(int);

    bool contains(MD5) const;
    bool replace(MediaPointer);
    int indexOf(MD5) const;

    //	Q_INVOKABLE void play(int = 0);
    Q_INVOKABLE MediaPointer next();
    Q_INVOKABLE MediaPointer prev();
    bool setReadOrder(QList<int>);

    virtual void set();
signals:
    void nameChanged();
    void countChanged();
    void isShuffleChanged();
    void play(MediaPointer);
    void currentIndexChanged();
    void playlistChanged();

public slots:
    Q_INVOKABLE virtual bool append(MediaPointer, int = -1);
    Q_INVOKABLE bool remove(int);
    Q_INVOKABLE MediaPointer at(int i) const;
    Q_INVOKABLE bool swap(int, int);
    Q_INVOKABLE bool clear();
};
