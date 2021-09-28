#include "expressionfactory.h"

QSharedPointer<Expression<bool>> ExpressionFactory::createInferior(QVariant& toTest, QVariant& value) {
    auto ret = QSharedPointer<InferiorExpression<QVariant&>>::create();
    ValueExpression<QVariant&> v1(value), v2(toTest);
    ret->setE1(v2.clone());
    ret->setE2(v1.clone());

    return ret;
}

QSharedPointer<Expression<bool>> ExpressionFactory::createSuperior(QVariant& toTest, QVariant& value)
{
    auto ret = QSharedPointer<SuperiorExpression<QVariant&>>::create();
    ValueExpression<QVariant&> v1(value), v2(toTest);
    ret->setE1(v2.clone());
    ret->setE2(v1.clone());

    return ret;
}

QSharedPointer<Expression<bool>> ExpressionFactory::createEqual(QVariant& toTest, QVariant& value)
{
    auto ret = QSharedPointer<EqualExpression<QVariant&>>::create();
    ValueExpression<QVariant&> v1(value), v2(toTest);
    ret->setE1(v2.clone());
    ret->setE2(v1.clone());

    return ret;
}

QSharedPointer<Expression<bool>> ExpressionFactory::createInferiorEqual(QVariant& toTest, QVariant& value)
{
    auto inf = QSharedPointer<InferiorExpression<QVariant&>>::create();
    ValueExpression<QVariant&> v1(value), v2(toTest);
    inf->setE1(v2.clone());
    inf->setE2(v1.clone());
    auto equal = QSharedPointer<EqualExpression<QVariant&>>::create();
    equal->setE1(v1.clone());
    equal->setE2(v2.clone());
    auto eor = QSharedPointer<OrExpression>::create();
    eor->setE1(equal->clone());
    eor->setE2(inf->clone());

    return eor;
}

QSharedPointer<Expression<bool>> ExpressionFactory::createSuperiorEqual(QVariant& toTest, QVariant& value)
{
    auto sup = QSharedPointer<SuperiorExpression<QVariant&>>::create();
    ValueExpression<QVariant&> v1(value), v2(toTest);
    sup->setE1(v2.clone());
    sup->setE2(v1.clone());
    auto equal = QSharedPointer<EqualExpression<QVariant&>>::create();
    equal->setE1(v1.clone());
    equal->setE2(v2.clone());
    auto eor = QSharedPointer<OrExpression>::create();
    eor->setE1(equal->clone());
    eor->setE2(sup->clone());

    return eor;
}

QSharedPointer<Expression<bool>> ExpressionFactory::createStart(QVariant& toTest, QVariant& value)
{
    auto ret = QSharedPointer<StartExpression>::create();
    ValueExpression<QVariant&> v1(value), v2(toTest);
    ret->setE1(v2.clone());
    ret->setE2(v1.clone());

    return ret;
}

QSharedPointer<Expression<bool>> ExpressionFactory::createEnd(QVariant& toTest, QVariant& value)
{
    auto ret = QSharedPointer<EndExpression>::create();
    ValueExpression<QVariant&> v1(value), v2(toTest);
    ret->setE1(v2.clone());
    ret->setE2(v1.clone());

    return ret;
}

QSharedPointer<Expression<bool>> ExpressionFactory::createContain(QVariant& toTest, QVariant& value)
{
    auto ret = QSharedPointer<ContainExpression>::create();
    ValueExpression<QVariant&> v1(value), v2(toTest);
    ret->setE1(v2.clone());
    ret->setE2(v1.clone());

    return ret;
}

QSharedPointer<Expression<bool>> ExpressionFactory::createReg(QVariant& toTest, QVariant& value)
{
    auto ret = QSharedPointer<RegExpression>::create();
    ValueExpression<QVariant&> v1(value), v2(toTest);
    ret->setE1(v2.clone());
    ret->setE2(v1.clone());

    return ret;
}
