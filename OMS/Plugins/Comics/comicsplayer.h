#pragma once

#include <QTemporaryDir>
#include <QProcess>

#include <Model/media.h>

class ComicsPlayer
{
    Q_DISABLE_COPY(ComicsPlayer)

private:
    QTemporaryDir* m_dir = nullptr;
    MediaPointer m_media;

public:
    ComicsPlayer() = default;
    ~ComicsPlayer();
    bool play(MediaPointer);

};

