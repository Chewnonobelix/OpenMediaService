#pragma once

#include <QObject>

#include <Model/media.h>

class AudioPlayer : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AudioPlayer)

    Q_PROPERTY(Media* media READ media NOTIFY mediaChanged CONSTANT)

private:
    MediaPointer m_media;

public:
    explicit AudioPlayer(QObject *parent = nullptr);

    void setMedia(MediaPointer);
    Media* media() const;

signals:
    void mediaChanged();
};

