#ifndef LIBRARY_H
#define LIBRARY_H

#include <QMap>
#include <QObject>

#include "media.h"
#include "playlist.h"
#include "libraryprobe.h"

class Library: public QObject
{
    Q_OBJECT

private:
    QString m_name;
    QSet<QString> m_sourceDir;

    MediaPlayerGlobal::MediaRole m_role;    
    QMap<MD5, MediaPointer> m_medias;    
    QList<PlayListPointer> m_playlists;
    
    LibraryProbe m_probe;

public:
    Library();
    ~Library();

    void probe();

public slots:
    void addProbedMedia(MD5, QString);
    void endProbe();
};

#endif // LIBRARY_H
