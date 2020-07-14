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
private:
    LibraryProbe m_probe;

    
public:
    Library();
    Library(const Library&);
    ~Library() = default;

    Library& operator = (const Library&);
    
    Q_INVOKABLE void probe();


public slots:
    
signals:

};
Q_DECLARE_METATYPE(Library)
#endif // LIBRARY_H
