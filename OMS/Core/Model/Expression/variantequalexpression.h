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
        auto ret = false;

        for(auto it: this->e1()->evaluate().toList())
            ret |= QVariant::compare(it, this->e2()->evaluate()) == QPartialOrdering::Equivalent;
        return ret;
    }
};

