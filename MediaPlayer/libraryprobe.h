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

class LibraryProbe
{
private:
    QSet<QByteArray> md5;
    QStringList filter;
    int counter;
    
public:
    LibraryProbe();
    ~LibraryProbe();
    
    void explore(QString = "./");
    QByteArray getMd5(QFileInfo);
    
};

#endif // LIBRARYPROBE_H
