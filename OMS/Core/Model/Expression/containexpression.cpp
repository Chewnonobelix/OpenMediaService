#include "containexpression.h"

QSharedPointer<Expression<bool>> ContainExpression::clone() const
{
    return QSharedPointer<ContainExpression>::create(*this);
}

bool ContainExpression::evaluate() const
{
    auto ret = false;

    auto v1 = this->e1()->evaluate().toList();
    auto v2 = this->e2()->evaluate().toList();

//    qDebug()<<"Wesh"<<v1<<v2;
    for(auto it: v1)
        for(auto it2: v2)
             ret |= it.toString().contains(it2.toString(), Qt::CaseInsensitive);

    return ret;
}
