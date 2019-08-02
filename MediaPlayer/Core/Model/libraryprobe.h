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

class LibraryProbe: public QThread
{
private:
protected:
    void run();

public:
    static QSet<QByteArray> global;
    static int globalCount;

    QStringList baseName;
    LibraryProbe();
    ~LibraryProbe();
    
    QSet<QByteArray> md5;
    QStringList filter;
    int counter;

    void explore(QString = "./");
    QByteArray getMd5(QFileInfo);
    
public slots:
    void onEnd();
};

#endif // LIBRARYPROBE_H
