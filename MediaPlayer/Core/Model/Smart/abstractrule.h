#pragma once

#include <Core/expression.h>

class AbstractRule
{
public:
    enum class Op {Superior, Inferior, Equal, Not, InferiorEqual, SuperiorEqual, Limit, And, Or, List, RegExp, Contain, Start, End};

    virtual QSharedPointer<Expression<bool>> create() = 0;
};

