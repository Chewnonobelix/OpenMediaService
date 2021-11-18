#include "libraryprobe.h"

Q_LOGGING_CATEGORY(libraryprobe, "library.probe")

LibraryProbe::LibraryProbe() {}

bool LibraryProbe::setSourceDir(QStringList list) {
    auto ret = m_sourceDir != list;

    if(ret)
        m_sourceDir = list;

    return ret;
}

bool LibraryProbe::setRole(MediaPlayerGlobal::MediaRole role) {
    auto ret = m_role != role;
    if(ret)
        m_role = role;
    return ret;
}

void LibraryProbe::onMediaFind(QString, MD5) {
    m_current++;
     qCDebug(libraryprobe) << m_total << m_current << double(m_current) / m_total * 100;
    setLastProbed(QDateTime::currentDateTime());

    emit currentChanged();

    emit isRunningChanged();
}

double LibraryProbe::current() const {
    if (m_total == 0)
        return 100;

    return (m_current * 10000 / m_total) / 100.0;
}

bool LibraryProbe::setPaths(QSet<QString> paths) {
    auto ret = m_paths != paths;

    if(ret)
        m_paths = paths;

    return ret;
}

bool LibraryProbe::isRunning() const { return current() < 100.0; }

bool LibraryProbe::probe() {
    //TODO
    connect(this, &LibraryProbe::mediaFind, this, &LibraryProbe::onMediaFind,
            Qt::UniqueConnection);

    QStringList filters;

    for (auto it : m_filters)
        filters << "*." + it;

    qCDebug(libraryprobe) << "Probe" << m_filters << filters;

    m_current = 0;
    m_queue.append(m_sourceDir);
    QList<QPointer<QThread>> list;

    for (auto i = 0; i < 16; i++) {
        m_threads << (QThread::create([this]() {
            sleep(10);
            while (current() < 100.0 && !m_infos.isEmpty()) {
                m_mutex.lock();
                if(m_infos.isEmpty()) {
                    m_mutex.unlock();
                    continue;
                }
                auto it = m_infos.dequeue();
                m_mutex.unlock();

                if (!m_paths.contains(it.absoluteFilePath()) &&
                        isValid(it.absoluteFilePath())) {

                    emit mediaFind(it.absoluteFilePath(), MD5());

                    m_mutex.lock();
                    m_paths << it.absoluteFilePath();
                    m_mutex.unlock();
                }

            }
        }));

        auto &last = m_threads.last();
        connect(last, &QThread::finished, [last, this]() {
            m_mutex.lock();
            m_threads.remove(m_threads.lastIndexOf(last));
            m_mutex.unlock();
            last->deleteLater();

            if (m_threads.count() == 0) {
                 qCDebug(libraryprobe) << "End probe";
                m_current = m_total - 1;
            }
        });
        last->start();
    }

    for (auto i = 0; i < 8; i++) {
        list << QThread::create([this, filters]() {
            QDir dir;

            for (auto i = 0; i < 10; i++) {
                while (!m_queue.isEmpty()) {
                    m_mutex.lock();
                    if (m_queue.isEmpty()) {
                        m_mutex.unlock();
                        continue;
                    }
                    auto it = m_queue.dequeue();
                    m_mutex.unlock();
                    dir.cd(it);

                    auto files = dir.entryInfoList(filters, QDir::AllEntries |
                                                   QDir::NoDotAndDotDot);
                    files.append(dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot));

                    for (auto it2 : files) {
                        if (it2.isDir()) {
                            m_mutex.lock();
                            m_queue.enqueue(it2.absoluteFilePath());
                            m_mutex.unlock();
                        } else {
                            m_mutex.lock();
                            m_total++;
                            m_infos.enqueue(it2);
                            m_mutex.unlock();
                        }
                    }
                }
            }
        });

        auto &last = list.last();
        connect(last, &QThread::finished, [last]() { last->deleteLater(); });

        last->start();
    }

    return true;
}

QDateTime LibraryProbe::lastProbed() const { return m_lastProbed; }

bool LibraryProbe::setLastProbed(QDateTime lp) {
    bool ret = m_lastProbed != lp;

    if(m_lastProbed != lp) {
        m_lastProbed = lp;
        emit lastProbedChanged();
    }
    return ret;
}

bool LibraryProbe::isValid(QString path) const {
    QFileInfo info(path);
    auto suffix = info.suffix().toLower();
    return m_filters.contains(suffix);
}

bool LibraryProbe::setFilters(QStringList filters) {
    bool ret = m_filters != filters;
    if(m_filters != filters)
        m_filters = filters;
    return ret;
}
