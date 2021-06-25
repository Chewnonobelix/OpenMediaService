#pragma once

#include <QList>
#include <QDateTime>

#include <Core/naryexpression.h>
#include <Core/valueexpression.h>
#include <Operation/Logic/conjonctiveform.h>
#include <Operation/Logic/disjonctiveform.h>

#include "playlist.h"

class SmartPlaylist;

typedef QSharedPointer<SmartPlaylist> SmartPlaylistPointer;

namespace N{
template<typename  T>
QString type(T) {
    return "all";
}
}

class MEDIAPLAYERCORE_EXPORT SmartPlaylist : public PlayList {
    Q_OBJECT

private:
    static QMultiMap<QString, QString> s_ops;



    struct AbstractRule {
        virtual QSharedPointer<Expression<bool>> create() const = 0;
    };

    struct Rule: public AbstractRule {
        QString field;
        QString value;
        QString op;

        QSharedPointer<Expression<bool>> create() const override;
    };

    struct Group: public AbstractRule {
        QString op;
        QVector<std::unique_ptr<AbstractRule>> list;

        QSharedPointer<Expression<bool>> create() const override;
    };

    bool isValid(MediaPointer) const;

public:
    SmartPlaylist() = default;
    using PlayList::PlayList;
    SmartPlaylist(const SmartPlaylist &) = default;
    ~SmartPlaylist() = default;

public slots:
    void append(MediaPointer, int = -1) override;
    void onMediaChanged(MediaPointer);
};
