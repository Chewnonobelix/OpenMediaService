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
    Op m_op;

public:
    SmartRule() = default;
    SmartRule(const SmartRule&) = default;
    ~SmartRule() = default;

    QSharedPointer<Expression<bool>> create() override;
    QSharedPointer<AbstractRule> clone() const override;
    QPartialOrdering compare(QSharedPointer<AbstractRule>) const override;
    void set(MediaPointer) override;

    QString field() const;
    void setField(QString);
    QVariant& value();
    QVariant value() const;
    void setValue(QVariant);
    QVariant& toTest();
    QVariant toTest() const;
    void setToTest(QVariant);
    Op op() const;
    void setOp(Op);
};
