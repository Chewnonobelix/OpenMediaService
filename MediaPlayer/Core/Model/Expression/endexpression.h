#pragma once

#include <Operation/Comparaison/comparaisonexpression.h>

class EndExpression: public ComparaisonExpression<QString>
{
public:
    EndExpression() = default;
    EndExpression(const EndExpression&) = default;
    ~EndExpression() = default;

    QSharedPointer<Expression<bool>> clone() const override;
    bool evaluate() const override;

};

