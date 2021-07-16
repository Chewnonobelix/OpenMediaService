#include "abstractrule.h"

QMultiMap<AbstractRule::Type, AbstractRule::Op> AbstractRule::s_ops = {{Type::Number, Op::Inferior},
                                                    {Type::Number, Op::InferiorEqual},
                                                    {Type::Number, Op::Superior},
                                                    {Type::Number, Op::SuperiorEqual},
                                                    {Type::Number, Op::Equal},
                                                    {Type::Number, Op::Limit}, //TODO
//                                                    {"all", "equal"},
//                                                    {"all", "inList"}, //TODO
//                                                    {"pre", "not"}, //TODO
                                                    {Type::StringContainer, Op::Contain}, //TODO
                                                    {Type::StringContainer, Op::End}, //TODO
                                                    {Type::StringContainer, Op::Start} //TODO
//                                                    {String, "reg"}, //TODO
//                                                    {"group", "and"},
//                                                    {"group", "or"}
                                                   };


AbstractRule::AbstractRule()
{
    setMetadata("id", QUuid::createUuid());
}
