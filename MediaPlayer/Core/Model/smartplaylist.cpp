#include "smartplaylist.h"

QMultiMap<QString, QString> SmartPlaylist::s_ops = {{"number", "inferior"},
                                                    {"number", "einferior"},
                                                    {"number", "superior"},
                                                    {"number", "esuperior"},
                                                    {"number", "equal"},
                                                    {"number", "born"},
                                                    {"all", "equal"},
                                                    {"all", "inList"},
                                                    {"pre", "not"},
                                                    {"string", "contain"},
                                                    {"string", "start"},
                                                    {"string", "end"},
                                                    {"string", "reg"},
                                                    {"group", "and"},
                                                    {"group", "or"}
                                                   };

bool SmartPlaylist::isValid(MediaPointer) const {
    if(m_rules.isEmpty())
        return true;
    if(m_expression.isNull())
        return false;

    return m_expression->evaluate();
}

void SmartPlaylist::append(MediaPointer m, int p) {
    if (isValid(m))
        PlayList::append(m, p);
}

void SmartPlaylist::onMediaChanged(MediaPointer m) {
    if (!m.isNull())
        append(m);
}


QSharedPointer<Expression<bool>> SmartPlaylist::Rule::create()
{
    QSharedPointer<ComparaisonExpression<QVariant&>> ret;
    if(op == "inferior") {
        ret = QSharedPointer<InferiorExpression<QVariant&>>::create();
        ValueExpression<QVariant&> v1(value), v2(toTest);
        ret->setE1(v1.clone());
        ret->setE2(v2.clone());
    }
    if(op == "superior") {
        ret = QSharedPointer<SuperiorExpression<QVariant&>>::create();
        ValueExpression<QVariant&> v1(value), v2(toTest);
        ret->setE1(v1.clone());
        ret->setE2(v2.clone());
    }
    if(op == "einferior") {
        auto inf = QSharedPointer<InferiorExpression<QVariant&>>::create();
        ValueExpression<QVariant&> v1(value), v2(toTest);
        inf->setE1(v1.clone());
        inf->setE2(v2.clone());
        auto equal = QSharedPointer<EqualExpression<QVariant&>>::create();
        equal->setE1(v1.clone());
        equal->setE2(v2.clone());
        auto eor = QSharedPointer<OrExpression>::create();
        eor->setE1(equal->clone());
        eor->setE2(inf->clone());
        return eor;
    }
    if(op == "esuperior") {
        auto sup = QSharedPointer<SuperiorExpression<QVariant&>>::create();
        ValueExpression<QVariant&> v1(value), v2(toTest);
        sup->setE1(v1.clone());
        sup->setE2(v2.clone());
        auto equal = QSharedPointer<EqualExpression<QVariant&>>::create();
        equal->setE1(v1.clone());
        equal->setE2(v2.clone());
        auto eor = QSharedPointer<OrExpression>::create();
        eor->setE1(equal->clone());
        eor->setE2(sup->clone());
        return eor;
    }

    return ret;
}

QSharedPointer<Expression<bool>> SmartPlaylist::Group::create()
{
    QSharedPointer<NaryExpression<bool>> ret;
    if(op == "and")
        ret = QSharedPointer<ConjonctiveForm>::create();
    else
        ret = QSharedPointer<DisjonctiveForm>::create();

    for(auto& it: list)
        ret->pushBack(it->create());

    return ret;
}
