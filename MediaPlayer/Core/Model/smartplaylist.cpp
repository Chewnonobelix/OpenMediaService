#include "smartplaylist.h"

QMultiMap<QString, QString> SmartPlaylist::s_ops = {{"number", "inferior"},
                                                    {"number", "einferior"},
                                                    {"number", "superior"},
                                                    {"number", "esuperior"},
                                                    {"number", "equal"},
                                                    {"number", "limit"}, //TODO
                                                    {"all", "equal"},
                                                    {"all", "inList"}, //TODO
                                                    {"pre", "not"}, //TODO
                                                    {"string", "contain"}, //TODO
                                                    {"string", "start"}, //TODO
                                                    {"string", "end"}, //TODO
                                                    {"string", "reg"}, //TODO
                                                    {"group", "and"},
                                                    {"group", "or"}
                                                   };

bool SmartPlaylist::isValid(MediaPointer m)
{
    if(m_rules.count() == 0)
        return true;

    if(m_expression.isNull())
        return false;

    m_rules.set(m);
    return m_expression->evaluate();
}

void SmartPlaylist::append(MediaPointer m, int p)
{
    if (isValid(m))
        PlayList::append(m, p);
}

void SmartPlaylist::onMediaChanged(MediaPointer m) {
    if (!m.isNull())
        append(m);
}

SmartGroup SmartPlaylist::rules() const
{
    return m_rules;
}

void SmartPlaylist::setRules(SmartGroup rule)
{
    m_rules = rule;
    rebuild();
}

void SmartPlaylist::rebuild()
{
    m_expression = m_rules.create();
}

