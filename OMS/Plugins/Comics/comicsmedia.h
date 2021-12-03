#pragma once

#include <QImage>
#include <QTemporaryDir>
#include <QDomDocument>
#include <QDomElement>

#include <Model/media.h>

class ComicsMedia
{
private:
    QSharedPointer<QTemporaryDir> m_extractDir;
    MediaPointer m_base;

public:
    ComicsMedia() = default;
    ComicsMedia(MediaPointer);

    QString cover() const;
    void initComicsInfo();

    QSharedPointer<QTemporaryDir> dir() const;
    MediaPointer base() const;

    void load();
    void unload();
};

