#include "startexpression.h"

QSharedPointer<Expression<bool>> StartExpression::clone() const
{
    return QSharedPointer<StartExpression>::create(*this);
}

bool StartExpression::evaluate() const
{
    return e2()->evaluate().startsWith(e1()->evaluate());
}
