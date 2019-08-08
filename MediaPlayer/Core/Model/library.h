#ifndef LIBRARY_H
#define LIBRARY_H

#include <QMap>
#include <QObject>
#include <QSharedPointer>
#include "media.h"
#include "playlist.h"
#include "libraryprobe.h"

class Library;

typedef QSharedPointer<Library> LibraryPointer;

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

    QString name() const;
    void setName(QString name);
    
    MediaPlayerGlobal::MediaRole role() const;
    void setRole(MediaPlayerGlobal::MediaRole role);
    
public slots:
    void addProbedMedia(MD5, QString);
    void endProbe();
    
signals:
    void s_addMedia(MediaPointer);
    void s_updateMedia(MediaPointer);
    void s_removeMedia(MediaPointer);
    
};

#endif // LIBRARY_H
