#pragma once

#include <Core/valueexpression.h>
#include <Operation/Logic/orexpression.h>
#include <Operation/Logic/andexpression.h>

#include <mediaplayercore_global.h>
#include "abstractrule.h"

#include <Model/Expression/variantequalexpression.h>
#include <Model/Expression/variantsuperiorexpression.h>
#include <Model/Expression/variantinferiorexpression.h>

#include <Model/Expression/expressionfactory.h>

class MEDIAPLAYERCORE_EXPORT SmartRule: public AbstractRule {
private:
    QVariant m_toTest;
    QVariant m_value;

public:
    SmartRule() = default;
    SmartRule(const SmartRule&) = default;
    SmartRule(const QJsonObject&);
    ~SmartRule() = default;

    using AbstractRule::AbstractRule;
    using AbstractRule::operator QJsonObject;

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
    Op op() const override;
    bool setOp(Op) override;
};
