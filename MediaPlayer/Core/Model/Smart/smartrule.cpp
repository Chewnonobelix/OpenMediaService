#include "smartrule.h"

SmartRule::SmartRule(const QJsonObject& json): AbstractRule(json)
{
    m_value = json["value"].toVariant();
}

QString SmartRule::field() const
{
    return metaData<QString>("field");
}

bool SmartRule::setField(QString newfield)
{
    return setMetadata("field", newfield);
}

QVariant& SmartRule::value()
{
    return m_value;
}

QVariant SmartRule::value() const
{
    return metaData<QVariant>("value");
}

bool SmartRule::setValue(QVariant newvalue)
{
    m_value = newvalue;
    return setMetadata("value", newvalue);
}

QVariant& SmartRule::toTest()
{
    return m_toTest;
}

QVariant SmartRule::toTest() const
{
    return m_toTest;
}

bool SmartRule::setToTest(QVariant newtoTest)
{
    auto ret = m_toTest != newtoTest;
    if(m_toTest == newtoTest)
        m_toTest = newtoTest;
    return ret;
}

AbstractRule::Op SmartRule::op() const
{
    return metaData<AbstractRule::Op>("op");
}

bool SmartRule::setOp(Op newop)
{
    return setMetadata("op", newop);
}

QSharedPointer<Expression<bool>> SmartRule::create()
{
    QSharedPointer<ComparaisonExpression<QVariant&>> ret;
    QSharedPointer<Expression<bool>> vret;

    switch(op()) {
    case Op::Inferior: {
        ret = QSharedPointer<InferiorExpression<QVariant&>>::create();
        ValueExpression<QVariant&> v1(value()), v2(toTest());
        ret->setE1(v2.clone());
        ret->setE2(v1.clone());
        vret = ret;
        break;
    }
    case Op::Superior: {
        ret = QSharedPointer<SuperiorExpression<QVariant&>>::create();
        ValueExpression<QVariant&> v1(value()), v2(toTest());
        ret->setE1(v2.clone());
        ret->setE2(v1.clone());
        vret = ret;
        break;
    }
    case Op::InferiorEqual: {
        auto inf = QSharedPointer<InferiorExpression<QVariant&>>::create();
        ValueExpression<QVariant&> v1(value()), v2(toTest());
        inf->setE1(v2.clone());
        inf->setE2(v1.clone());
        auto equal = QSharedPointer<EqualExpression<QVariant&>>::create();
        equal->setE1(v1.clone());
        equal->setE2(v2.clone());
        auto eor = QSharedPointer<OrExpression>::create();
        eor->setE1(equal->clone());
        eor->setE2(inf->clone());
        vret = eor;
        break;
    }
    case Op::SuperiorEqual: {
        auto sup = QSharedPointer<SuperiorExpression<QVariant&>>::create();
        ValueExpression<QVariant&> v1(value()), v2(toTest());
        sup->setE1(v2.clone());
        sup->setE2(v1.clone());
        auto equal = QSharedPointer<EqualExpression<QVariant&>>::create();
        equal->setE1(v1.clone());
        equal->setE2(v2.clone());
        auto eor = QSharedPointer<OrExpression>::create();
        eor->setE1(equal->clone());
        eor->setE2(sup->clone());
        vret = eor;
        break;
    }
    case Op::Equal:
    case Op::Not:
    case Op::Limit:
    case Op::List:
    case Op::RegExp:
    case Op::Contain:
    case Op::Start:
    case Op::End:
    default:
        vret = QSharedPointer<ValueExpression<bool>>::create(true);
        break;
    }
    return vret;
}

QSharedPointer<AbstractRule> SmartRule::clone() const
{
    return DesignPattern::factory<SmartRule>(*this);
}

QPartialOrdering SmartRule::compare(AbstractRulePointer other) const
{
    if(field().isEmpty() || !value().isValid())
        return QPartialOrdering::Equivalent;

    auto r = other.dynamicCast<SmartRule>();
    auto ret = !r.isNull() && (field() == r->field()) &&
            (value() == r->value()) && (toTest() == r->toTest()) &&
            (op() == r->op()) ? QPartialOrdering::Equivalent : QPartialOrdering::Unordered;
    return ret;
}

bool SmartRule::set(MediaPointer m)
{
    return setToTest(m->metaData<QVariant>(field()));
}
