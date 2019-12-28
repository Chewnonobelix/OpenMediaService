#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QMap>

typedef QByteArray MD5;

Q_DECLARE_METATYPE(MD5)
namespace MediaPlayerGlobal
{
    Q_NAMESPACE

    enum MediaRole {Undefined, Audio, Video, Comics, Books, Image, Game};
    Q_ENUM_NS(MediaRole)
    
    MediaRole getRole(QString path);

    template<class T>
    QSet<T> toSet(QList<T> l)
    {
        return QSet<T>(l.begin(), l.end());
    }
}

Q_DECLARE_METATYPE(MediaPlayerGlobal::MediaRole)

#endif // GLOBAL_H
