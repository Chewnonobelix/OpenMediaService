#pragma once

#include <Operation/Logic/conjonctiveform.h>
#include <Operation/Logic/disjonctiveform.h>

#include <mediaplayercore_global.h>

#include "abstractrule.h"
#include "smartrule.h"

class MEDIAPLAYERCORE_EXPORT SmartGroup: public AbstractRule {
private:
    Op m_op;
    QList<QSharedPointer<AbstractRule>> m_list;

public:
    SmartGroup() = default;
    SmartGroup(const SmartGroup&);
    ~SmartGroup() = default;

    QSharedPointer<Expression<bool>> create() override;
    QSharedPointer<AbstractRule> clone() const override;
    QPartialOrdering compare(QSharedPointer<AbstractRule>) const override;

    bool setOp(Op);
    Op op() const;

    void add(bool = false);
    void remove(int);
    QSharedPointer<AbstractRule> operator[](int) const;
    int count() const;
};

