#include "endexpression.h"

QSharedPointer<Expression<bool>> EndExpression::clone() const
{
    return QSharedPointer<EndExpression>::create(*this);
}

bool EndExpression::evaluate() const
{
    auto ret = false;

    auto v1 = this->e1()->evaluate().toList();
    auto v2 = this->e2()->evaluate().toList();

    for(auto it: v1)
        for(auto it2: v2)
        ret |= it.toString().endsWith(it2.toString(), Qt::CaseInsensitive);

    return ret;
}
