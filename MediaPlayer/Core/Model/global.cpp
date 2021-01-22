#include "global.h"
#include <QDebug>

using namespace MediaPlayerGlobal;

MediaRole MediaPlayerGlobal::getRole(QString path) {
	QMap<QString, MediaRole> map;
	map["mp3"] = MediaRole::Audio;
	map["ogg"] = MediaRole::Audio;
	map["flac"] = MediaRole::Audio;
	map["wav"] = MediaRole::Audio;

	map["cbr"] = MediaRole::Comics;
	map["cbz"] = MediaRole::Comics;
	map["pdf"] = MediaRole::Comics;

	map["epub"] = MediaRole::Books;

	auto ext = path.split(".").last();
	//	qDebug() << "Last" << ext;
	return map[ext];
}
