#pragma once

#include <QCryptographicHash>
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QFileInfo>
#include <QMutex>
#include <QPointer>
#include <QQueue>
#include <QSet>
#include <QString>
#include <QThread>
#include <QTime>

#include <mediaplayercore_global.h>

#include <metadata.h>

#include "Model/global.h"

class MEDIAPLAYERCORE_EXPORT LibraryProbe : public QThread {
	Q_OBJECT

	Q_PROPERTY(double current READ current NOTIFY currentChanged)
	Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
	Q_PROPERTY(QDateTime lastProbed READ lastProbed WRITE setLastProbed NOTIFY
								 lastProbedChanged)

private:
	QSet<QString> m_paths;
	QStringList m_filters;

	QStringList m_sourceDir;
	MediaPlayerGlobal::MediaRole m_role;
	int m_total = 0, m_current = 0;
	QQueue<QFileInfo> m_infos;
	QQueue<QString> m_queue;
	QList<QPointer<QThread>> m_threads;
	QDateTime m_lastProbed = QDateTime::currentDateTime();

	QMutex m_mutex;

protected:
public:
	LibraryProbe();
	~LibraryProbe() = default;

	void setSourceDir(QStringList);
	void setRole(MediaPlayerGlobal::MediaRole);
	void setPaths(QSet<QString>);
	QDateTime lastProbed() const;
	void setLastProbed(QDateTime);

	void probe();

	double current() const;
	bool isRunning() const;

	bool isValid(QString path) const;
	void setFilters(QStringList);

signals:
	void mediaFind(QString, MD5);
	void currentChanged();
	void isRunningChanged();
	void lastProbedChanged();

public slots:
	void onMediaFind(QString, MD5);
};
