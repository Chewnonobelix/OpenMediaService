#include "audioplayer.h"

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject{parent}
{

}

void AudioPlayer::setMedia(MediaPointer m)
{
    m_media = m;

    emit mediaChanged();
}

Media* AudioPlayer::media() const
{
    return m_media.data();
}
