#include "startexpression.h"

QSharedPointer<Expression<bool>> StartExpression::clone() const
{
    return QSharedPointer<StartExpression>::create(*this);
}

bool StartExpression::evaluate() const
{
    auto ret = false;

    for(auto it: this->e1()->evaluate().toList())
        ret |= it.toString().startsWith(this->e2()->evaluate().toString(), Qt::CaseInsensitive);
    return ret;
}
