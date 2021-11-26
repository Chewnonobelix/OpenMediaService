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
    ComicsMedia(MediaPointer);

    QImage cover() const;
};

