#include "regexpression.h"

QSharedPointer<Expression<bool>> RegExpression::clone() const
{
    return QSharedPointer<RegExpression>::create(*this);
}

bool RegExpression::evaluate() const
{
    auto ret = false;

    for(auto it: this->e1()->evaluate().toList())
        ret |= it.toString().contains(QRegularExpression(this->e2()->evaluate().toString()));
    return ret;
}
