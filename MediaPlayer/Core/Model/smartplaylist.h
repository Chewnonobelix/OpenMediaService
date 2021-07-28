#pragma once

#include <QList>
#include <QDateTime>
#include <QThread>
#include <QPointer>
#include <QQueue>

#include <Core/naryexpression.h>
#include <Core/valueexpression.h>
#include <Operation/Logic/conjonctiveform.h>
#include <Operation/Logic/disjonctiveform.h>
#include <Operation/Comparaison/equalexpression.h>
#include <Operation/Comparaison/inferiorexpression.h>
#include <Operation/Comparaison/superiorexpression.h>
#include <Operation/Logic/orexpression.h>

#include "Expression/variantsuperiorexpression.h"
#include "Expression/variantinferiorexpression.h"
#include "Expression/variantequalexpression.h"

#include "playlist.h"

#include "Smart/smartgroup.h"
#include "Smart/smartrule.h"

class SmartPlaylist;

typedef QSharedPointer<SmartPlaylist> SmartPlaylistPointer;

class MEDIAPLAYERCORE_EXPORT SmartPlaylist : public PlayList {
    Q_OBJECT

private:

    bool isValid(MediaPointer);

    SmartGroupPointer m_rules = SmartGroupPointer::create();
    QSharedPointer<Expression<bool>> m_expression;
    QPointer<QThread> m_thread = nullptr;
    QQueue<MediaPointer> m_queue;;

public:
    SmartPlaylist();
    using PlayList::PlayList;
    SmartPlaylist(const QJsonObject&);
    SmartPlaylist(const SmartPlaylist &) = default;
    ~SmartPlaylist() = default;

    operator QJsonObject() const override;

    SmartGroupPointer rules() const;
    SmartGroup* rule() const;
    bool setRules(SmartGroupPointer);

    Q_INVOKABLE bool rebuild();
    void set() override;

public slots:
    void append(MediaPointer, int = -1) override;
    void onMediaChanged(MediaPointer);

signals:
    void rulesChanged();
};
