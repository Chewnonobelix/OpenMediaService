#include "global.h"

using namespace MediaPlayerGlobal;

MediaRole MediaPlayerGlobal::getRole(QString path)
{
    QMap<QString, MediaRole> map;
    map["mp3"] = Audio;
    map["ogg"] = Audio;
    map["flac"] = Audio;
    map["wav"] = Audio;
    
    map["cbr"] = Comics;
    map["cbz"] = Comics;
    map["pdf"] = Comics;
    
    map["epub"] = Books;
    
    map["jpg"] = Image;
    map["jpeg"] = Image;
    map["bmp"] = Image;
    map["png"] = Image;
    
    
    auto ext = path.split(".").last();
    
    
    return map[ext];
}
