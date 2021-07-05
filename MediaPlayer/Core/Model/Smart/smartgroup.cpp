#include "smartgroup.h"

SmartGroup::SmartGroup(const SmartGroup& g): AbstractRule(g), m_op(g.op())
{
    for(auto it: g.m_list) {
        m_list<<it->clone();
    }
}

QPartialOrdering SmartGroup::compare(QSharedPointer<AbstractRule> other) const
{
    auto ret =  QPartialOrdering::Equivalent;

    auto g = other.dynamicCast<SmartGroup>();
    ret = !g.isNull() && (g->count() == count()) && (g->op() == op()) ? QPartialOrdering::Equivalent : QPartialOrdering::Unordered;

    for(auto it = 0; it < m_list.count() && ret == QPartialOrdering::Equivalent; it++) {
        ret = m_list[it]->compare((*g)[it]);
    }

    return ret;
}

QSharedPointer<AbstractRule> SmartGroup::clone() const
{
    return DesignPattern::factory<SmartGroup>(*this);
}

QSharedPointer<Expression<bool>> SmartGroup::create()
{
    QSharedPointer<NaryExpression<bool>> ret;

    switch(op()) {
    case AbstractRule::Op::Or:
        ret = QSharedPointer<DisjonctiveForm>::create();
    case AbstractRule::Op::And:
    default:
        ret = QSharedPointer<ConjonctiveForm>::create();
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

QSharedPointer<AbstractRule> SmartGroup::add(bool group)
{
    if(group)
        m_list<<QSharedPointer<SmartGroup>::create();
    else
        m_list<<QSharedPointer<SmartRule>::create();

    return m_list.last();
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

void SmartGroup::set(MediaPointer m)
{
    for(auto it: m_list)
        it->set(m);
}
