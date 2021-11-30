#pragma once

#include <QImage>
#include <QTemporaryDir>

#include <Model/media.h>

class ComicsMedia
{
private:
    QSharedPointer<QTemporaryDir> m_extractDir;
    MediaPointer m_base;

public:
    ComicsMedia() = default;
    ComicsMedia(MediaPointer);

    QImage cover() const;
    QSharedPointer<QTemporaryDir> dir() const;
    MediaPointer base() const;

    void load();
    void unload();
};

