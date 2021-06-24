#include "smartplaylist.h"

QMultiMap<QString, QString> SmartPlaylist::s_ops = {{"number", "inferior"},
                                                    {"number", "einferior"},
                                                    {"number", "superior"},
                                                    {"number", "esuperior"},
                                                    {"number", "equal"},
                                                    {"all", "equal"},
                                                    {"all", "not"},
                                                    {"string", "contain"},
                                                    {"string", "start"},
                                                    {"string", "end"},
                                                    {"string", "reg"},
                                                    {"group", "and"},
                                                    {"group", "or"}
                                                   };
namespace N {
template<>
QString type (double) {
    return "number";
}

template<>
QString type (int) {
    return "number";
}

template<>
QString type (QDate) {
    return "number";
}

template<>
QString type (QDateTime) {
    return "number";
}

template<>
QString type (QString) {
    return "string";
}
}

bool SmartPlaylist::isValid(MediaPointer) const { return true; }

void SmartPlaylist::append(MediaPointer m, int p) {
    if (isValid(m))
        PlayList::append(m, p);
}

void SmartPlaylist::onMediaChanged(MediaPointer m) {
    if (!m.isNull())
        append(m);
}

QSharedPointer<Expression<bool>> SmartPlaylist::Rule::create() const
{
    auto ret = QSharedPointer<ValueExpression<bool>>::create();
    return ret;
}

QSharedPointer<Expression<bool>> SmartPlaylist::Group::create() const
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
