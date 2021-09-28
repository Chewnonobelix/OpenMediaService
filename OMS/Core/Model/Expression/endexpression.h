#pragma once

#include <QVariant>

#include <Operation/Comparaison/comparaisonexpression.h>

class EndExpression: public ComparaisonExpression<QVariant&>
{
public:
    EndExpression() = default;
    EndExpression(const EndExpression&) = default;
    ~EndExpression() = default;

    QSharedPointer<Expression<bool>> clone() const override;
    bool evaluate() const override;

};

