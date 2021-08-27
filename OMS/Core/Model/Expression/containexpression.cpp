#include "containexpression.h"

QSharedPointer<Expression<bool>> ContainExpression::clone() const
{
    return QSharedPointer<ContainExpression>::create(*this);
}

bool ContainExpression::evaluate() const
{
    auto ret = false;

    for(auto it: this->e1()->evaluate().toList())
        ret |= it.toString().contains(this->e2()->evaluate().toString(), Qt::CaseInsensitive);
    return ret;
}
