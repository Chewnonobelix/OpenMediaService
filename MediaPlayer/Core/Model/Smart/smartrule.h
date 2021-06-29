#pragma once

#include <Core/valueexpression.h>
#include <Operation/Logic/orexpression.h>
#include <Operation/Logic/andexpression.h>

#include "abstractrule.h"

#include "../Expression/variantequalexpression.h"
#include "../Expression/variantsuperiorexpression.h"
#include "../Expression/variantinferiorexpression.h"

class SmartRule: public AbstractRule {
private:
    QString m_field;
    QVariant m_value;
    QVariant m_toTest;
    Op m_op;

public:
    QSharedPointer<Expression<bool>> create() override;

    QString field() const;
    void setField(QString);
    QVariant& value();
    void setValue(QVariant);
    QVariant& toTest();
    void setToTest(QVariant);
    Op op() const;
    void setOp(Op);
};
