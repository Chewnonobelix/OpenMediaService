#include "smartrule.h"

SmartRule::SmartRule(const QJsonObject& json): AbstractRule(json)
{
    auto value = json["value"].toArray();

    QStringList stringValues;

    for(auto it: value)
        stringValues<<it.toString();

    setValue(stringValues);
}

SmartRule::operator QJsonObject() const
{
    auto ret = AbstractRule::operator QJsonObject();

    ret["value"] = QJsonArray::fromStringList(m_value.toStringList());
    return ret;
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
    case Op::Superior:
        return ExpressionFactory::createSuperior(toTest(), value());
        break;
    case Op::InferiorEqual:
        return ExpressionFactory::createInferiorEqual(toTest(), value());
        break;
    case Op::SuperiorEqual:
        return ExpressionFactory::createSuperiorEqual(toTest(), value());
        break;
    case Op::RegExp:
        return ExpressionFactory::createReg(toTest(), value());
        break;
    case Op::Contain:
        return ExpressionFactory::createContain(toTest(), value());
        break;
    case Op::Start:
        return ExpressionFactory::createStart(toTest(), value());
        break;
    case Op::End:
        return ExpressionFactory::createEnd(toTest(), value());
        break;
    case Op::Equal:
        return ExpressionFactory::createEqual(toTest(), value());
        break;
    case Op::Not:
    case Op::Limit:
    case Op::List:
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
    if(m->metadataList().contains(field()))
        return setToTest(m->metaData<QVariant>(field()));

    return false;
}
