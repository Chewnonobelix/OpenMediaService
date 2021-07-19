#include "smartgroup.h"

SmartGroup::SmartGroup(): AbstractRule() {}
SmartGroup::SmartGroup(const QJsonObject& json): AbstractRule(json)
{
    auto array = json["list"].toArray();

    for(auto it: array) {
        auto obj = it.toObject();
        if(obj["isGroup"].toBool(false))
            m_list<<DesignPattern::factory<SmartGroup>(obj);
        else
            m_list<<DesignPattern::factory<SmartRule>(obj);

        auto g = m_list.last().dynamicCast<SmartGroup>();
        if(g) {
            for(auto it = 0; it < g->count() ; it ++) {
                (*g)[it]->setParent(g);
            }
        }
    }
}

SmartGroup::operator QJsonObject() const
{
    auto ret = AbstractRule::operator QJsonObject();

    ret["isGroup"] = true;
    QJsonArray array;

    for(auto it: m_list)
    {
        array<<(QJsonObject)(*it);
    }

    ret["list"] = array;
    return ret;
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
        setMetadata("op", o);
        return true;
    default:
        return false;
    }
}

AbstractRule::Op SmartGroup::op() const
{
    return metaData<AbstractRule::Op>("op");
}

QSharedPointer<AbstractRule> SmartGroup::add(bool group)
{
    if(group)
        m_list<<QSharedPointer<SmartGroup>::create();
    else
        m_list<<QSharedPointer<SmartRule>::create();

    m_list.last()->setParent(sharedFromThis());
    return m_list.last();
}

bool SmartGroup::remove(QUuid id)
{
    auto it = m_list.removeIf([id](AbstractRulePointer p) {
        return p->id() == id;
    });

    return it > 0;
}

QSharedPointer<AbstractRule> SmartGroup::operator[](int i) const
{
    if(i < m_list.count() && i >= 0)
        return m_list[i];

    return QSharedPointer<AbstractRule>();
}

QSharedPointer<AbstractRule> SmartGroup::operator[](int i)
{
    if(i < m_list.count() && i >= 0)
        return m_list[i];

    return QSharedPointer<AbstractRule>();
}

int SmartGroup::count() const
{
    return m_list.count();
}

bool SmartGroup::set(MediaPointer m)
{
    auto ret = true;
    for(auto it: m_list)
        ret &= it->set(m);
    return ret;
}
