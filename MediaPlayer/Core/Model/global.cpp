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

	map["jpg"] = MediaRole::Image;
	map["jpeg"] = MediaRole::Image;
	map["bmp"] = MediaRole::Image;
	map["png"] = MediaRole::Image;

	map["ts"] = MediaRole::Video;
	map["mp4"] = MediaRole::Video;
	map["mkv"] = MediaRole::Video;
	map["avi"] = MediaRole::Video;

	auto ext = path.split(".").last();
	//	qDebug() << "Last" << ext;
	return map[ext];
}
