#include "libraryprobe.h"

void LibraryProbe::setSourceDir(QStringList list) { m_sourceDir = list; }

void LibraryProbe::setRole(MediaPlayerGlobal::MediaRole role) { m_role = role; }

void LibraryProbe::onMediaFind(QString, MD5) {
	m_current++;
	qDebug() << m_total << m_current << double(m_current) / m_total * 100;
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
	QDir dir;
	QQueue<QString> queue;
	queue.append(m_sourceDir);
	QQueue<QFileInfo> infos;

	while (!queue.isEmpty()) {
		auto it = queue.dequeue();
		if (it.startsWith("file:///"))
			it.remove("file:///");

		dir.cd(it);
		auto files = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);

		for (auto it2 : files) {
			if (it2.isDir()) {
				queue.enqueue(it2.absoluteFilePath());
			} else {
				if (MediaPlayerGlobal::getRole(it2.fileName()) == m_role) {
					infos.enqueue(it2);
				}
			}
		}
	}

	qDebug() << "Infos" << infos.size();
	m_total = infos.size();
	for (auto it = 0; it < 8; it++) {
		qDebug() << std::min((int(infos.size() / 8) * it), int(infos.size()))
						 << int(infos.size() / 8);
		QPointer<QThread> t(QThread::create(
				[this](auto l, int number) {
					for (auto it : l) {
						if (!m_paths.contains(it.absoluteFilePath())) {
							QCryptographicHash hasher(QCryptographicHash::Sha256);
							QFile file(it.absoluteFilePath());
							file.open(QIODevice::ReadOnly);
							hasher.addData(&file);
							auto h = hasher.result();
							file.close();

							emit mediaFind(it.absoluteFilePath(), h);

							m_paths << it.absoluteFilePath();
						}
					}
				},
				infos.mid(
						std::min(((int(infos.size() / 8) + 1) * it), int(infos.size())),
						int(infos.size() / 8) + 1),
				it));

		connect(t, &QThread::finished, [t]() {
			qDebug() << "Destroy";
			t->deleteLater();
		});

		t->start();
	}
}
