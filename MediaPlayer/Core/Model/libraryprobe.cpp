#include "libraryprobe.h"

LibraryProbe::LibraryProbe() {}

void LibraryProbe::setSourceDir(QStringList list) { m_sourceDir = list; }

void LibraryProbe::setRole(MediaPlayerGlobal::MediaRole role) { m_role = role; }

void LibraryProbe::onMediaFind(QString, MD5) {
	m_current++;
	qDebug() << m_total << m_current << double(m_current) / m_total * 100;
	setLastProbed(QDateTime::currentDateTime());

	emit currentChanged();

	emit isRunningChanged();
}

double LibraryProbe::current() const {
	if (m_total == 0)
		return 100;

	return (m_current * 10000 / m_total) / 100.0;
}

void LibraryProbe::setPaths(QSet<QString> paths) { m_paths = paths; }

bool LibraryProbe::isRunning() const { return current() != 100.0; }

void LibraryProbe::probe() {
	connect(this, &LibraryProbe::mediaFind, this, &LibraryProbe::onMediaFind,
					Qt::UniqueConnection);

	m_current = 0;
	m_queue.append(m_sourceDir);
	QList<QPointer<QThread>> list;

	for (auto i = 0; i < 16; i++) {
		m_threads << (QThread::create([this]() {
			sleep(10);
			while (current() < 100.0 && !m_infos.isEmpty()) {
				m_mutex.lock();
				auto it = m_infos.dequeue();
				m_mutex.unlock();
				if (!m_paths.contains(it.absoluteFilePath())) {
					QCryptographicHash hasher(QCryptographicHash::Sha256);
					QFile file(it.absoluteFilePath());
					file.open(QIODevice::ReadOnly);
					hasher.addData(&file);
					auto h = hasher.result();
					file.close();

					emit mediaFind(it.absoluteFilePath(), h);

					m_mutex.lock();
					m_paths << it.absoluteFilePath();
					m_mutex.unlock();
				}
			}
		}));

		auto &last = m_threads.last();
		connect(last, &QThread::finished, [last, this]() {
			m_threads.remove(m_threads.lastIndexOf(last));
			last->deleteLater();
		});
		last->start();
	}

	for (auto i = 0; i < 8; i++) {
		list << QThread::create([this]() {
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

					auto files =
							dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);

					for (auto it2 : files) {
						if (it2.isDir()) {
							m_mutex.lock();
							m_queue.enqueue(it2.absoluteFilePath());
							m_mutex.unlock();
						} else {
							if (MediaPlayerGlobal::getRole(it2.fileName()) == m_role) {
								m_mutex.lock();
								m_total++;
								m_infos.enqueue(it2);
								m_mutex.unlock();
							}
						}
					}
				}
			}
		});

		auto &last = list.last();
		connect(last, &QThread::finished, [last]() { last->deleteLater(); });

		last->start();
	}
}

QDateTime LibraryProbe::lastProbed() const { return m_lastProbed; }

void LibraryProbe::setLastProbed(QDateTime lp) {
	m_lastProbed = lp;
	emit lastProbedChanged();
}
