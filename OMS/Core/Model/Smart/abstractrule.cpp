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
                                                    {Type::String, Op::Start}
                                                   };


AbstractRule::AbstractRule()
{
    setMetadata("id", QUuid::createUuid());
}
