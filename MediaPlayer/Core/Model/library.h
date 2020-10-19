#ifndef LIBRARY_H
#define LIBRARY_H

#include <QMap>
#include <QObject>
#include <QSharedPointer>
#include "media.h"
#include "playlist.h"
#include "libraryprobe.h"
#include "metadata.h"

using namespace MediaPlayerGlobal;

class Library;

typedef QSharedPointer<Library> LibraryPointer;

class Library: public QObject, public MetaData
{
    Q_OBJECT

    /**
      Property:
      -Medias
      -Playlists
      -Name
      -Role
      -Source dir
      -last probed

      methods:
      -probe
      -add manually (dir or file)

      **/
    
    Q_PROPERTY(QUuid id READ id CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(MediaPlayerGlobal::MediaRole role READ role CONSTANT)
    Q_PROPERTY(bool isShared READ isShared WRITE setShared NOTIFY isSharedChanged)
    Q_PROPERTY(QDateTime lastProbed READ lastProbed WRITE setLastProbed NOTIFY lastProbedChanged)
    Q_PROPERTY(QDateTime lastUpdate READ lastUpdate WRITE setLastUpdate NOTIFY lastUpdateChanged)
    Q_PROPERTY(QSet<QString> sourceDir READ sourceDir NOTIFY sourceDirChanged)


private:
    LibraryProbe m_probe;
    QMap<MD5, MediaPointer> m_medias;
    
public:
    Library() = default;
    Library(const Library&);
    ~Library() = default;

    Library& operator = (const Library&);

    bool friend operator<(LibraryPointer, LibraryPointer);

    QUuid id() const;
    void setId(QUuid);
    QString name() const;
    void setName(QString);
    MediaPlayerGlobal::MediaRole role() const;
    void setRole(MediaPlayerGlobal::MediaRole);
    bool isShared() const;
    void setShared(bool);
    QDateTime lastProbed() const;
    void setLastProbed(QDateTime);
    QSet<QString> sourceDir() const;
    QDateTime lastUpdate() const;
    void setLastUpdate(QDateTime);
    
public slots:
    Q_INVOKABLE void probe();
    Q_INVOKABLE bool addMedia(QString, MD5 = "");
    Q_INVOKABLE bool removeMedia(QString);
    Q_INVOKABLE QMap<MD5, MediaPointer> medias(MD5 = "") const;
    Q_INVOKABLE bool addSourceDir(QString);
    Q_INVOKABLE bool removeSourceDir(QString);
     
signals:
    void nameChanged(QString);
    void isSharedChanged(bool);
    void lastProbedChanged(QDateTime);
    void sourceDirChanged(QSet<QString>);
    void mediasChanged();
    void lastUpdateChanged();
};
Q_DECLARE_METATYPE(Library)
#endif // LIBRARY_H
