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
    
    
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(MediaPlayerGlobal::MediaRole role READ role CONSTANT)
    Q_PROPERTY(QDateTime lastProbed READ lastProbed NOTIFY s_updateLastProbed)
    Q_PROPERTY(QStringList sourceDir READ sourceDir NOTIFY s_updateSourceDirList)
    
private:
    QString m_name;
    QSet<QString> m_sourceDir;

    MediaPlayerGlobal::MediaRole m_role;    
    QMap<MD5, MediaPointer> m_medias;    
    QList<PlayListPointer> m_playlists;
    QDateTime m_lastProbed;
    
    LibraryProbe m_probe;

public:
    Library();
    Library(const Library&);
    ~Library();

    Library& operator = (const Library&);
    
    Q_INVOKABLE void probe();

    QString name() const;
    void setName(QString name);
    
    MediaPlayerGlobal::MediaRole role() const;
    void setRole(MediaPlayerGlobal::MediaRole role);
    
    QMap<MD5, MediaPointer> medias() const;
    void setMedias(const QMap<MD5, MediaPointer> &medias);
    
    Q_INVOKABLE void addSourceDir(QString);
    QList<QString> sourceDir() const;
    Q_INVOKABLE void removeSourceDir(QString);
    
    QDateTime lastProbed() const;
    void setLastProbed(QDateTime lastProbed);
    
public slots:
    void addProbedMedia(MD5, QString);
    void endProbe();
    void removeMedia(MD5);
    bool addMedia(QString);
    
signals:
    void s_addMedia(MediaPointer);
    void s_updateMedia(MediaPointer);
    void s_removeMedia(MediaPointer);
    void s_updateLastProbed(QDateTime);
    void s_updateSourceDir(QSet<QString>);
    void s_updateSourceDirList(QList<QString>);
};

Q_DECLARE_METATYPE(Library)
#endif // LIBRARY_H
