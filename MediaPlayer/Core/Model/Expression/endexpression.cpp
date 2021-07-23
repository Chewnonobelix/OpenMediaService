#include "endexpression.h"

QSharedPointer<Expression<bool>> EndExpression::clone() const
{
    return QSharedPointer<EndExpression>::create(*this);
}

bool EndExpression::evaluate() const
{
    return e2()->evaluate().endsWith(e1()->evaluate());
}
