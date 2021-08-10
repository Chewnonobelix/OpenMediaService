#pragma once

#include <Core/expression.h>
#include <designpattern.h>
#include <metadata.h>

#include <Model/global.h>
#include <Model/media.h>


using namespace MediaPlayerGlobal;

class AbstractRule;

using AbstractRulePointer = QSharedPointer<AbstractRule>;

class AbstractRule: public MetaData, public QEnableSharedFromThis<AbstractRule>
{
    Q_GADGET
    AbstractRulePointer m_parent;

public:
    enum class Op {Undefined, Superior, Inferior, Equal, Not, InferiorEqual, SuperiorEqual, Limit, And, Or,
                   List, RegExp, Contain, Start, End};
    Q_ENUM(Op)

    static QMultiMap<Type, Op> s_ops;


    AbstractRule();
    using MetaData::MetaData;

    using MetaData::operator QJsonObject;

    inline QUuid id() const {return metaData<QUuid>("id");}
    virtual bool set(MediaPointer) = 0;
    virtual QSharedPointer<Expression<bool>> create() = 0;
    virtual AbstractRulePointer clone() const = 0;
    virtual QPartialOrdering compare(AbstractRulePointer) const = 0;
    virtual Op op() const = 0;
    virtual bool setOp(Op) = 0;
    inline AbstractRulePointer parent() const {return m_parent;}
    inline bool setParent(AbstractRulePointer p) {
        auto ret = m_parent != p;
        if(ret) m_parent = p;
        return ret;
    }
};

