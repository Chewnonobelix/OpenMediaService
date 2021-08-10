#pragma once

#include <Operation/Comparaison/comparaisonexpression.h>

class StartExpression: public ComparaisonExpression<QString>
{
public:
    StartExpression() = default;
    StartExpression(const StartExpression&) = default;
    ~StartExpression() = default;

    QSharedPointer<Expression<bool>> clone() const override;
    bool evaluate() const override;

};

