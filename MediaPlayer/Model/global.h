#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QMap>

typedef QByteArray MD5;

namespace MediaPlayerGlobal
{
    Q_NAMESPACE

    enum MediaRole {Undefined, Audio, Video, Comics, Books, Image, Game};
    Q_ENUM_NS(MediaRole)
    
    MediaRole getRole(QString path);
}

#endif // GLOBAL_H
