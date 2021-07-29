#include "smartplaylist.h"


SmartPlaylist::SmartPlaylist()
{
    m_rules->add();

    m_thread = QThread::create([this]() {
        while(1) {
            if(!m_queue.isEmpty()) {
                auto m = m_queue.dequeue();
                if (!isValid(m)) {
                    removeAll(m);

                    for(auto& it: m_readOrder)
                        it--;
                }
                else if(!contains(m)) {
                    PlayList::append(m);
                    for(auto& it: m_readOrder)
                        it++;
                }

                emit playlistChanged();
            }

            m_thread->msleep(500);
        }
    });

    m_thread->start();
}

SmartPlaylist::SmartPlaylist(const QJsonObject& json): PlayList(json)
{
    m_rules = DesignPattern::factory<SmartGroup>(json["smart"].toObject());

    for(auto it = 0; it < m_rules->count() ; it ++) {
        (*m_rules)[it]->setParent(m_rules);
    }

    rebuild();
    m_thread = QThread::create([this]() {
        while(1) {
            if(!m_queue.isEmpty()) {
                auto m = m_queue.dequeue();
                if (!isValid(m)) {
                    removeAll(m);

                    for(auto& it: m_readOrder)
                        it--;
                }
                else if(!contains(m)) {
                    PlayList::append(m);
                    for(auto& it: m_readOrder)
                        it++;
                }

                emit playlistChanged();
            }

            m_thread->msleep(500);
        }
    });

    m_thread->start();
}

SmartPlaylist::operator QJsonObject() const
{
    auto ret = PlayList::operator QJsonObject();

    ret["smart"] = (QJsonObject)(*m_rules);

    return ret;
}

bool SmartPlaylist::isValid(MediaPointer m)
{
    if(m_rules->count() == 0)
        return true;

    if(m_expression.isNull())
        return false;

    m_rules->set(m);

    return m_expression->evaluate();
}

bool SmartPlaylist::append(MediaPointer m, int)
{
    m_queue.enqueue(m);
    return true;
}

void SmartPlaylist::onMediaChanged(MediaPointer m) {
    if (!m.isNull())
        append(m);
}

SmartGroupPointer SmartPlaylist::rules() const
{
    return m_rules;
}

SmartGroup* SmartPlaylist::rule() const
{
    return m_rules.data();
}

bool SmartPlaylist::setRules(SmartGroupPointer rule)
{
    auto ret = m_rules != rule;
    if(ret) {
        m_rules = rule;
        ret &= rebuild();
        emit rulesChanged();
    }
    return ret;
}

bool SmartPlaylist::rebuild()
{
    m_expression = m_rules->create();

    return !m_expression.isNull();
}

void SmartPlaylist::set()
{
    PlayList::set();
    connect(this, &SmartPlaylist::rulesChanged, this, &PlayList::playlistChanged);
}
