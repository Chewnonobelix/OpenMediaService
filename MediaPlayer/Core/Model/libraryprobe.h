#ifndef LIBRARYPROBE_H
#define LIBRARYPROBE_H

#include <QDebug>
#include <QCryptographicHash>
#include <QString>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSet>
#include <QTime>
#include <QThread>
#include <QElapsedTimer>

class LibraryProbe: public QThread
{
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
