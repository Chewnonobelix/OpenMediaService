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
    static QMultiMap<QString, QString> s_ops;

    bool isValid(MediaPointer) const;

    SmartGroup m_rules;
    QSharedPointer<Expression<bool>> m_expression;

public:
    SmartPlaylist() = default;
    using PlayList::PlayList;
    SmartPlaylist(const SmartPlaylist &) = default;
    ~SmartPlaylist() = default;
    SmartGroup rules() const;
    void setRules(SmartGroup);

    Q_INVOKABLE void rebuild();
public slots:
    void append(MediaPointer, int = -1) override;
    void onMediaChanged(MediaPointer);
};
