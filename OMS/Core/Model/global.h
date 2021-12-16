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

enum class Type {Number = 2, String = 4, Date = 6, Container = 1,
                NumberContainer = Number | Container, StringContainer = String | Container};
Q_FLAG_NS(Type)

using Tag = QPair<QUuid, QString>;

template <class T> QSet<T> toSet(QList<T> l) {
	return QSet<T>(l.begin(), l.end());
}
} // namespace MediaPlayerGlobal
