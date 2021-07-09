#pragma once

#include <Core/expression.h>
#include <designpattern.h>

#include <Model/media.h>


class AbstractRule;

using AbstractRulePointer = QSharedPointer<AbstractRule>;

class AbstractRule: public QEnableSharedFromThis<AbstractRule>
{
    Q_GADGET
    QUuid m_id = QUuid::createUuid();
    AbstractRulePointer m_parent;

public:
    enum class Op {Undefined, Superior, Inferior, Equal, Not, InferiorEqual, SuperiorEqual, Limit, And, Or, List, RegExp, Contain, Start, End};
    Q_ENUM(Op)

    inline QUuid id() const {return m_id;}
    virtual bool set(MediaPointer) = 0;
    virtual QSharedPointer<Expression<bool>> create() = 0;
    virtual AbstractRulePointer clone() const = 0;
    virtual QPartialOrdering compare(AbstractRulePointer) const = 0;

    inline AbstractRulePointer parent() const {return m_parent;}
    inline bool setParent(AbstractRulePointer p) {
        auto ret = m_parent != p;
        if(ret) m_parent = p;
        return ret;
    }
};

