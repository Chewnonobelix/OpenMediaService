#include "smartplaylist.h"


SmartPlaylist::SmartPlaylist()
{
    m_rules->add();
}

SmartPlaylist::SmartPlaylist(const QJsonObject& json): PlayList(json)
{
    m_rules = DesignPattern::factory<SmartGroup>(json["smart"].toObject());

    for(auto it = 0; it < m_rules->count() ; it ++) {
        (*m_rules)[it]->setParent(m_rules);
    }

    rebuild();
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

QFuture<bool> SmartPlaylist::creating()
{
    return QtConcurrent::run([this]() {
        bool ret = m_queue.isEmpty();
        while(!m_queue.isEmpty()) {
            auto locker = new QMutexLocker(&m_queueMutex);
            auto m = m_queue.dequeue();
            delete locker;

            if (!isValid(m)) {
                ret = false;
                removeIf([m](MediaPointer it) {
                    return it->id() == m->id();
                });

                for(auto& it: m_readOrder)
                    it--;
                emit countChanged();
            }
            else if(!contains(m->id())) {
                ret = PlayList::append(m).result();
                for(auto& it: m_readOrder)
                    it++;
                emit countChanged();
            }

        }
        return ret;

    });
}

QFuture<bool> SmartPlaylist::append(MediaPointer m, int)
{
    QMutexLocker locker(&m_queueMutex);
    m_queue.enqueue(m);

    if(!m_results.isRunning())
        m_results = creating();

    return m_results;
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
