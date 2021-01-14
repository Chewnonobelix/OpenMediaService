#pragma once

#include <QMap>
#include <QObject>

#include <mediaplayercore_global.h>

typedef QByteArray MD5;

Q_DECLARE_METATYPE(MD5)

namespace MediaPlayerGlobal {
Q_NAMESPACE
Q_NAMESPACE_EXPORT(MEDIAPLAYERCORE_EXPORT)

enum class MediaRole { Undefined, Audio, Video, Comics, Books, Image, Game };
Q_ENUM_NS(MediaRole)

MediaRole getRole(QString path);

template <class T> QSet<T> toSet(QList<T> l) {
	return QSet<T>(l.begin(), l.end());
}
} // namespace MediaPlayerGlobal
