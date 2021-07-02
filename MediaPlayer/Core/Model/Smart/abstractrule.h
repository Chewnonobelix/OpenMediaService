#pragma once

#include <Core/expression.h>
#include <designpattern.h>

class AbstractRule
{
public:
    enum class Op {Superior, Inferior, Equal, Not, InferiorEqual, SuperiorEqual, Limit, And, Or, List, RegExp, Contain, Start, End};

    virtual QSharedPointer<Expression<bool>> create() = 0;
    virtual QSharedPointer<AbstractRule> clone() const = 0;
    virtual QPartialOrdering compare(QSharedPointer<AbstractRule>) const = 0;
};

