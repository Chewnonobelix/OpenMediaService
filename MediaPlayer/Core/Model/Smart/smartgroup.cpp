#include "smartgroup.h"

QSharedPointer<Expression<bool>> SmartGroup::create()
{
    QSharedPointer<NaryExpression<bool>> ret;

    switch(op()) {
    case AbstractRule::Op::And:
        ret = QSharedPointer<ConjonctiveForm>::create();
        break;
    case AbstractRule::Op::Or:
        ret = QSharedPointer<DisjonctiveForm>::create();
    default:
        break;
    }
    for(auto& it: m_list)
        ret->pushBack(it->create());

    return ret;
}

bool SmartGroup::setOp(Op o)
{
    switch(o) {
    case AbstractRule::Op::And:
    case AbstractRule::Op::Or:
        m_op = o;
        return true;
    default:
        return false;
    }
}

AbstractRule::Op SmartGroup::op() const
{
    return m_op;
}

void SmartGroup::add(bool group)
{
    if(group)
        m_list<<QSharedPointer<SmartGroup>::create();
    else
        m_list<<QSharedPointer<SmartRule>::create();
}

void SmartGroup::remove(int i)
{
    if(i < m_list.count() && i >= 0)
        m_list.removeAt(i);
}

QSharedPointer<AbstractRule> SmartGroup::operator[](int i) const
{
    if(i < m_list.count() && i >= 0)
        return m_list[i];

    return QSharedPointer<AbstractRule>();
}

int SmartGroup::count() const
{
    return m_list.count();
}
