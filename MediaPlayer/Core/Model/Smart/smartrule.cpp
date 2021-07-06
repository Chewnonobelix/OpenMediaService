#include "smartrule.h"

QString SmartRule::field() const
{
    return m_field;
}

void SmartRule::setField(QString newfield)
{
    m_field = newfield;
}

QVariant& SmartRule::value()
{
    return m_value;
}

QVariant SmartRule::value() const
{
    return m_value;
}

void SmartRule::setValue(QVariant newvalue)
{
    m_value = newvalue;
}

QVariant& SmartRule::toTest()
{
    return m_toTest;
}

QVariant SmartRule::toTest() const
{
    return m_toTest;
}

void SmartRule::setToTest(QVariant newtoTest)
{
    m_toTest = newtoTest;
}

AbstractRule::Op SmartRule::op() const
{
    return m_op;
}

void SmartRule::setOp(Op newop)
{
    m_op = newop;
}

QSharedPointer<Expression<bool>> SmartRule::create()
{
    QSharedPointer<ComparaisonExpression<QVariant&>> ret;

    switch(op()) {
    case Op::Inferior: {
        ret = QSharedPointer<InferiorExpression<QVariant&>>::create();
        ValueExpression<QVariant&> v1(value()), v2(toTest());
        ret->setE1(v2.clone());
        ret->setE2(v1.clone());
        break;
    }
    case Op::Superior: {
        ret = QSharedPointer<SuperiorExpression<QVariant&>>::create();
        ValueExpression<QVariant&> v1(value()), v2(toTest());
        ret->setE1(v2.clone());
        ret->setE2(v1.clone());
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
        return eor;
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
        return eor;
        break;
    }
    default:
        return QSharedPointer<ValueExpression<bool>>::create(true);
        break;
    }
    return ret;
}

QSharedPointer<AbstractRule> SmartRule::clone() const
{
    return DesignPattern::factory<SmartRule>(*this);
}

QPartialOrdering SmartRule::compare(QSharedPointer<AbstractRule> other) const
{
    if(field().isEmpty() || !value().isValid())
        return QPartialOrdering::Equivalent;

    auto r = other.dynamicCast<SmartRule>();
    auto ret = !r.isNull() && (field() == r->field()) &&
            (value() == r->value()) && (toTest() == r->toTest()) &&
            (op() == r->op()) ? QPartialOrdering::Equivalent : QPartialOrdering::Unordered;
    return ret;
}

void SmartRule::set(MediaPointer m)
{
    setToTest(m->metaData<QVariant>(field()));
}
