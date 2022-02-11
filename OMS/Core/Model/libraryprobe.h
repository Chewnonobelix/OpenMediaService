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
#include <QLoggingCategory>

#include <mediaplayercore_global.h>

#include <metadata.h>
#include "media.h"

#include "Model/global.h"

class MEDIAPLAYERCORE_EXPORT LibraryProbe : public QThread {
	Q_OBJECT

	Q_PROPERTY(double current READ current NOTIFY currentChanged)
	Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
	Q_PROPERTY(QDateTime lastProbed READ lastProbed WRITE setLastProbed NOTIFY
								 lastProbedChanged)

    friend class ProbeThread;
    friend class CreateThread;

private:
	QSet<QString> m_paths;
	QStringList m_filters;

	QStringList m_sourceDir;
	MediaPlayerGlobal::MediaRole m_role;
	int m_total = 0, m_current = 0;
	QQueue<QFileInfo> m_infos;
	QQueue<QString> m_queue;
	QList<QPointer<QThread>> m_threads;
    QList<QPointer<QThread>> list;

	QDateTime m_lastProbed = QDateTime::currentDateTime();

    QMutex m_mutexSearch, m_mutexCreate, m_mutexDelete;


protected:
public:
	LibraryProbe();
	~LibraryProbe() = default;

    bool setSourceDir(QStringList);
    bool setRole(MediaPlayerGlobal::MediaRole);
    bool setPaths(QSet<QString>);
	QDateTime lastProbed() const;
    bool setLastProbed(QDateTime);

    bool probe();

	double current() const;
	bool isRunning() const;

	bool isValid(QString path) const;
    bool setFilters(QStringList);

signals:
    void mediaFind(MediaPointer);
	void currentChanged();
	void isRunningChanged();
	void lastProbedChanged();

public slots:
    void onMediaFind(MediaPointer);
};

class ProbeThread: public QThread
{
    Q_OBJECT
private:
    LibraryProbe& m_parent;

protected:
    void run() override;

public:
    ProbeThread(LibraryProbe&, QObject* = nullptr);
    ~ProbeThread() = default;
};

class CreateThread: public QThread
{
    Q_OBJECT
private:
    LibraryProbe& m_parent;

protected:
    void run() override;

public:
    CreateThread(LibraryProbe&, QObject* = nullptr);
    ~CreateThread() = default;

signals:
    void sCreateMedia(MediaPointer);
};
