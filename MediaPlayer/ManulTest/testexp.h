#pragma once

#include <Core/expression.h>

template<class T>
class TestExp: public Expression<bool>
{
public:
    TestExp() = default;
    TestExp(const TestExp<T>&) = default;
    ~TestExp() = default;

    QSharedPointer<Expression<T>> e1;
    QSharedPointer<Expression<T>> e2;

    QSharedPointer<Expression<bool>> clone() const override
    {
        return QSharedPointer<TestExp<T>>::create(*this);
    }

    bool evaluate() const override
    {
        return this->e1->evaluate() == this->e2->evaluate();
    }
};

