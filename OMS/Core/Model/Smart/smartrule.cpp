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
    if(ret)
        m_toTest = newtoTest.toList().isEmpty() ? QVariantList({newtoTest}) : newtoTest.toList();
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
    case Op::Inferior:
        return ExpressionFactory::createInferior(toTest(), value());
        break;
    case Op::Superior: {
        return ExpressionFactory::createSuperior(toTest(), value());
        break;
    case Op::InferiorEqual:
        return ExpressionFactory::createInferiorEqual(toTest(), value());
        break;
    case Op::SuperiorEqual:
        return ExpressionFactory::createSuperiorEqual(toTest(), value());
        break;
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
