#pragma once

#include <QCryptographicHash>
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QFileInfo>
#include <QPointer>
#include <QQueue>
#include <QSet>
#include <QString>
#include <QThread>
#include <QTime>

#include "Model/global.h"

class LibraryProbe : public QThread {
	Q_OBJECT

	Q_PROPERTY(double current READ current NOTIFY currentChanged)
	Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)

private:
	QSet<QString> m_paths;
	QStringList m_sourceDir;
	MediaPlayerGlobal::MediaRole m_role;
	int m_total = 0, m_current = 0;

protected:
public:
	LibraryProbe() = default;
	~LibraryProbe() = default;

	void setSourceDir(QStringList);
	void setRole(MediaPlayerGlobal::MediaRole);
	void setPaths(QSet<QString>);

	void probe();

	double current() const;
	bool isRunning() const;

signals:
	void mediaFind(QString, MD5);
	void currentChanged();
	void isRunningChanged();

public slots:
	void onMediaFind(QString, MD5);
};
