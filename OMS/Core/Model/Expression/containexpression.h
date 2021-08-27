#pragma once

#include <QVariant>

#include <Operation/Comparaison/comparaisonexpression.h>

class ContainExpression: public ComparaisonExpression<QVariant&>
{
public:
    ContainExpression()= default;
    ContainExpression(const ContainExpression&) = default;
    ~ContainExpression() = default;

    QSharedPointer<Expression<bool>> clone() const override;
    bool evaluate() const override;
};

