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
        auto ret = false;

        for(auto it: this->e1()->evaluate().toList())
            ret |= QVariant::compare(it, this->e2()->evaluate()) == QPartialOrdering::Greater;
        return ret;
    }
};

