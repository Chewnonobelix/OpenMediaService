#pragma once

#include <QList>
#include <QDateTime>

#include <Core/naryexpression.h>
#include <Core/valueexpression.h>
#include <Operation/Logic/conjonctiveform.h>
#include <Operation/Logic/disjonctiveform.h>
#include <Operation/Comparaison/equalexpression.h>
#include <Operation/Comparaison/inferiorexpression.h>
#include <Operation/Comparaison/superiorexpression.h>
#include <Operation/Logic/orexpression.h>

#include "Expression/variantsuperiorexpression.h"

#include "playlist.h"

class SmartPlaylist;

typedef QSharedPointer<SmartPlaylist> SmartPlaylistPointer;

class MEDIAPLAYERCORE_EXPORT SmartPlaylist : public PlayList {
    Q_OBJECT

private:
    static QMultiMap<QString, QString> s_ops;

    struct AbstractRule {
        virtual QSharedPointer<Expression<bool>> create() = 0;
    };

    struct Rule: public AbstractRule {
        QString field;
        QVariant value;
        QVariant toTest;
        QString op;

        QSharedPointer<Expression<bool>> create() override;
    };

    struct Group: public AbstractRule {
        QString op;
        QList<std::unique_ptr<AbstractRule>> list;

        QSharedPointer<Expression<bool>> create() override;
    };

    bool isValid(MediaPointer) const;

    QList<Rule> m_rules;
    QSharedPointer<Expression<bool>> m_expression;

public:
    SmartPlaylist() = default;
    using PlayList::PlayList;
    SmartPlaylist(const SmartPlaylist &) = default;
    ~SmartPlaylist() = default;

public slots:
    void append(MediaPointer, int = -1) override;
    void onMediaChanged(MediaPointer);
};
