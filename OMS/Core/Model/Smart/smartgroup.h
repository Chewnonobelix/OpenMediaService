#pragma once

#include <Operation/Logic/conjonctiveform.h>
#include <Operation/Logic/disjonctiveform.h>

#include <mediaplayercore_global.h>

#include "abstractrule.h"
#include "smartrule.h"

class SmartGroup;

using SmartGroupPointer = QSharedPointer<SmartGroup>;

class MEDIAPLAYERCORE_EXPORT SmartGroup: public AbstractRule {
private:
    Op m_op;
    QList<QSharedPointer<AbstractRule>> m_list;

public:
    SmartGroup();
    SmartGroup(const SmartGroup&) = default;
    ~SmartGroup() = default;

    SmartGroup(const QJsonObject&);

    operator QJsonObject() const override;

    QSharedPointer<Expression<bool>> create() override;
    QSharedPointer<AbstractRule> clone() const override;
    QPartialOrdering compare(QSharedPointer<AbstractRule>) const override;
    bool set(MediaPointer) override;

    bool setOp(Op) override;
    Op op() const override;

    QSharedPointer<AbstractRule> add(bool = false);
    bool remove(QUuid);
    QSharedPointer<AbstractRule> operator[](int) const;
    QSharedPointer<AbstractRule> operator[](int);
    int count() const;
};

