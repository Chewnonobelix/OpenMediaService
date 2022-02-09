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
        list << new ProbeThread(*this);

        auto &last = list.last();
        connect(last, &QThread::finished, [last, this]() {
            QMutexLocker lock(&m_mutexDelete);
            list.removeAll(last);
            qCDebug(libraryprobe)<<"Search finish";
        });

        last->start();
    }

    for (auto i = 0; i < 16; i++) {
        m_threads <<  new CreateThread(*this);

        auto last = dynamic_cast<CreateThread*>(m_threads.last().data());

        connect(last, &CreateThread::sCreateMedia, this, &LibraryProbe::onMediaFind, Qt::DirectConnection);
        connect(last, &CreateThread::sCreateMedia, this, &LibraryProbe::mediaFind, Qt::DirectConnection);

        connect(last, &QThread::finished, [last, this]() {
            QMutexLocker lock(&m_mutexDelete);
            m_threads.removeAll(last);

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

ProbeThread::ProbeThread(LibraryProbe& probe, QObject * parent): QThread(parent), m_parent(probe) {}

void ProbeThread::run()
{
    auto& queue = m_parent.m_queue;
    auto& searchMutex = m_parent.m_mutexSearch;
    auto& createMutex = m_parent.m_mutexCreate;
    auto& infos = m_parent.m_infos;
    auto& total = m_parent.m_total;

    QStringList filters;
    for (auto it : m_parent.m_filters)
        filters << "*." + it;


    while (!queue.isEmpty()) {
        QDir dir;
        QMutexLocker locker(&searchMutex);
        if (queue.isEmpty()) {
            continue;
        }
        auto it = queue.dequeue();
        dir.cd(it);

        auto files = dir.entryInfoList(filters, QDir::AllEntries |
                                                    QDir::NoDotAndDotDot);
        files.append(dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot));

        for (auto it2 : files) {
            if (it2.isDir()) {
                queue.enqueue(it2.absoluteFilePath());
            } else if(!infos.contains(it2)){
                QMutexLocker createLock(&createMutex);
                total++;
                infos.enqueue(it2);
            }
        }
    }
}

CreateThread::CreateThread(LibraryProbe& probe, QObject * parent): QThread(parent), m_parent(probe) {}

void CreateThread::run()
{
    auto& infos = m_parent.m_infos;
    auto& paths = m_parent.m_paths;
    auto& queue = m_parent.m_queue;
    auto& total = m_parent.m_total;
    auto& createMutex = m_parent.m_mutexCreate;

    while (!infos.isEmpty() || !queue.isEmpty()) {
        QMutexLocker createLock(&createMutex);
        if(infos.isEmpty()) {
            continue;
        }
        auto it = infos.dequeue();

        if(paths.contains(it.absolutePath()))
            total --;
        else if (m_parent.isValid(it.absoluteFilePath())) {
            auto media = Media::createMedia(it.absoluteFilePath());

            emit sCreateMedia(media);

            paths << it.absoluteFilePath();
        }
    }
}
