#include "regexpression.h"

QSharedPointer<Expression<bool>> RegExpression::clone() const
{
    return QSharedPointer<RegExpression>::create(*this);
}

bool RegExpression::evaluate() const
{
    auto ret = false;

    auto v1 = this->e1()->evaluate().toList();
    auto v2 = this->e2()->evaluate().toList();

    for(auto it: v1)
        for(auto it2: v2)
            ret |= it.toString().contains(QRegularExpression(it2.toString()));

    return ret;
}
