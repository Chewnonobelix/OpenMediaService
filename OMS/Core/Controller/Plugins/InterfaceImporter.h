#pragma once

#include <QObject>

#include <mediaplayercore_global.h>

#include <Model/media.h>
#include <Model/smartplaylist.h>

class MEDIAPLAYERCORE_EXPORT InterfaceImporter: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(InterfaceImporter)

public:
    InterfaceImporter(QObject* parent = nullptr);
    ~InterfaceImporter() = default;

    virtual bool import(QString) = 0;
    virtual QString name() const = 0;
    virtual QStringList filters() const = 0;

signals:
    void findWatchfolder(QString);
    void findMedia(MediaPointer);
    void findPlaylist(PlaylistPointer);
    void findSmartPlaylist(SmartPlaylistPointer);
};
