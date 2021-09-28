#include "startexpression.h"

QSharedPointer<Expression<bool>> StartExpression::clone() const
{
    return QSharedPointer<StartExpression>::create(*this);
}

bool StartExpression::evaluate() const
{
    auto ret = false;

    auto v1 = this->e1()->evaluate().toList();
    auto v2 = this->e2()->evaluate().toList();

    for(auto it: v1)
        for(auto it2: v2)
           ret |= it.toString().startsWith(it2.toString(), Qt::CaseInsensitive);

    return ret;
}
