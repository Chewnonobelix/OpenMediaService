#pragma once

#include <QString>
#include <QObject>
#include <QTemporaryDir>
#include <QProcess>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>

#include <Model/media.h>
#include <Model/smartplaylist.h>

class ComicsRackImporter: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ComicsRackImporter)

public:
    ComicsRackImporter(QObject* = nullptr);
    ~ComicsRackImporter() = default;
    bool import(QString);

signals:
    void findWatchfolder(QString);
    void findMedia(MediaPointer);
    void findPlaylist(PlaylistPointer);
    void findSmartPlaylist(SmartPlaylistPointer);
};

