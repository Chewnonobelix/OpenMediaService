#pragma once

#include <QVariant>
#include <Operation/Comparaison/equalexpression.h>

template<>
class EqualExpression<QVariant&>: public ComparaisonExpression<QVariant&>
{
public:
    QSharedPointer<Expression<bool>> clone() const override
    {
        return QSharedPointer<EqualExpression<QVariant&>>::create(*this);
    }

    bool evaluate() const override
    {
        return QVariant::compare(this->e1()->evaluate(), this->e2()->evaluate()) == QPartialOrdering::Equivalent;
    }
};

