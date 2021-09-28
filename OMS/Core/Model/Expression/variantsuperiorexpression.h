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

        auto v1 = this->e1()->evaluate().toList();
        auto v2 = this->e2()->evaluate().toList();

        for(auto it: v1)
            for(auto it2: v2)
            ret |= QVariant::compare(it, it2) == QPartialOrdering::Greater;
        return ret;
    }
};

