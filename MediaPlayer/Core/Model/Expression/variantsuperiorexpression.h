#pragma once

#include <QVariant>
#include <Operation/Comparaison/superiorexpression.h>

template<>
class SuperiorExpression<QVariant&>: public ComparaisonExpression<QVariant&>
{
public:
    QSharedPointer<Expression<bool>> clone() const override
    {
        return QSharedPointer<SuperiorExpression<QVariant&>>::create(*this);
    }

    bool evaluate() const override
    {
        return QVariant::compare(this->e1()->evaluate(), this->e2()->evaluate()) == QPartialOrdering::Greater;
    }
};

