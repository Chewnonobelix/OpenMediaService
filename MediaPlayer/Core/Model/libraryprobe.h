#ifndef LIBRARYPROBE_H
#define LIBRARYPROBE_H

#include <QCryptographicHash>
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QFileInfo>
#include <QSet>
#include <QString>
#include <QThread>
#include <QTime>

class LibraryProbe : public QThread {
	Q_OBJECT

private:
protected:
public:
	LibraryProbe() = default;
	~LibraryProbe() = default;

signals:

public slots:
};

#endif // LIBRARYPROBE_H
