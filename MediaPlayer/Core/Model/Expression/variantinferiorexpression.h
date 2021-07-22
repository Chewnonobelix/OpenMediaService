#pragma once

#include <QVariant>
#include <Operation/Comparaison/inferiorexpression.h>

template<>
class InferiorExpression<QVariant&>: public ComparaisonExpression<QVariant&>
{
public:
    QSharedPointer<Expression<bool>> clone() const override
    {
        return QSharedPointer<InferiorExpression<QVariant&>>::create(*this);
    }

    bool evaluate() const override
    {
        return QVariant::compare(this->e1()->evaluate(), this->e2()->evaluate()) == QPartialOrdering::Less;
    }
};

