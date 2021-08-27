#pragma once

#include <QVariant>
#include <QRegularExpression>

#include <Operation/Comparaison/comparaisonexpression.h>

class RegExpression: public ComparaisonExpression<QVariant&>
{
public:
    RegExpression()= default;
    RegExpression(const RegExpression&) = default;
    ~RegExpression() = default;

    QSharedPointer<Expression<bool>> clone() const override;
    bool evaluate() const override;
};

