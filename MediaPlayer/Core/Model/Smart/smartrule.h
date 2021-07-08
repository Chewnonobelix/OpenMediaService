#pragma once

#include <Core/valueexpression.h>
#include <Operation/Logic/orexpression.h>
#include <Operation/Logic/andexpression.h>

#include <mediaplayercore_global.h>
#include "abstractrule.h"

#include <Model/Expression/variantequalexpression.h>
#include <Model/Expression/variantsuperiorexpression.h>
#include <Model/Expression/variantinferiorexpression.h>

class MEDIAPLAYERCORE_EXPORT SmartRule: public AbstractRule {
private:
    QString m_field;
    QVariant m_value;
    QVariant m_toTest;
    Op m_op = Op::Undefined;

public:
    SmartRule() = default;
    SmartRule(const SmartRule&) = default;
    ~SmartRule() = default;

    QSharedPointer<Expression<bool>> create() override;
    AbstractRulePointer clone() const override;
    QPartialOrdering compare(AbstractRulePointer) const override;
    bool set(MediaPointer) override;

    QString field() const;
    bool setField(QString);
    QVariant& value();
    QVariant value() const;
    bool setValue(QVariant);
    QVariant& toTest();
    QVariant toTest() const;
    bool setToTest(QVariant);
    Op op() const;
    bool setOp(Op);
};
