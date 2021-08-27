#include "endexpression.h"

QSharedPointer<Expression<bool>> EndExpression::clone() const
{
    return QSharedPointer<EndExpression>::create(*this);
}

bool EndExpression::evaluate() const
{
    auto ret = false;

    for(auto it: this->e1()->evaluate().toList())
        ret |= it.toString().endsWith(this->e2()->evaluate().toString(), Qt::CaseInsensitive);
    return ret;
}
