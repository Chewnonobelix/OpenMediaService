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

void LibraryProbe::onMediaFind(MediaPointer) {
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

void LibraryProbe::creating()
{
    while (!m_infos.isEmpty() || !m_queue.isEmpty()) {
        QMutexLocker createLock(&m_mutexCreate);
        if(m_infos.isEmpty()) {
            continue;
        }
        auto it = m_infos.dequeue();

        if(m_paths.contains(it.absolutePath()))
            m_total --;
        else if (isValid(it.absoluteFilePath())) {
            auto media = Media::createMedia(it.absoluteFilePath());

            emit mediaFind(media);
            onMediaFind(media);

            m_paths << it.absoluteFilePath();
        }
    }
}

void LibraryProbe::search()
{
    QStringList filters;

    for (auto it : m_filters)
        filters << "*." + it;

    QDir dir;

    for (auto i = 0; i < 10; i++) {
        while (!m_queue.isEmpty()) {
            QMutexLocker locker(&m_mutexSearch);
            if (m_queue.isEmpty()) {
                continue;
            }
            auto it = m_queue.dequeue();
            dir.cd(it);

            auto files = dir.entryInfoList(filters, QDir::AllEntries |
                                                        QDir::NoDotAndDotDot);
            files.append(dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot));

            for (auto it2 : files) {
                if (it2.isDir()) {
                    m_queue.enqueue(it2.absoluteFilePath());
                } else if(!m_infos.contains(it2)){
                    QMutexLocker createLock(&m_mutexCreate);
                    m_total++;
                    m_infos.enqueue(it2);
                }
            }
        }
    }
}

bool LibraryProbe::probe() {
    QStringList filters;
    m_threads.clear();
    list.clear();

    for (auto it : m_filters)
        filters << "*." + it;

    qCDebug(libraryprobe) << "Probe" << m_filters << filters;

    m_current = 0;
    m_queue.append(m_sourceDir);



    for (auto i = 0; i < 8; i++) {
        list << QThread::create(&LibraryProbe::search, this);

        auto &last = list.last();
        connect(last, &QThread::finished, [last, this]() {
            list.removeAll(last);
            last->deleteLater();
            qCDebug(libraryprobe)<<"Search finish";
        });

        last->start();
    }

    for (auto i = 0; i < 16; i++) {
        m_threads <<  QThread::create(&LibraryProbe::creating, this);

        auto &last = m_threads.last();
        connect(last, &QThread::finished, [last, this]() {
            if (m_threads.count() == 0) {
                qCDebug(libraryprobe) << "End probe";
                m_current = m_total;
            }
        });
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
