#include "abstractrule.h"

using namespace MediaPlayerGlobal;

QMultiMap<Type, AbstractRule::Op> AbstractRule::s_ops = {
    {Type::Number, Op::Inferior},
    {Type::Number, Op::InferiorEqual},
    {Type::Number, Op::Superior},
    {Type::Number, Op::SuperiorEqual},
    {Type::Number, Op::Equal},
    {Type::Number, Op::Limit},
    {Type::String, Op::Contain},
    {Type::String, Op::End},
    {Type::String, Op::Start},
    {Type::NumberContainer, Op::Inferior},
    {Type::NumberContainer, Op::InferiorEqual},
    {Type::NumberContainer, Op::Superior},
    {Type::NumberContainer, Op::SuperiorEqual},
    {Type::NumberContainer, Op::Equal},
    {Type::NumberContainer, Op::Limit},
    {Type::StringContainer, Op::Contain},
    {Type::StringContainer, Op::End},
    {Type::StringContainer, Op::Start}
};


AbstractRule::AbstractRule()
{
    setMetadata("id", QUuid::createUuid());
}
