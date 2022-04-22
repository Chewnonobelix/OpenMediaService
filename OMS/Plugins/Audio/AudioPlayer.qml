import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtMultimedia

import MediaPlayer.Components 1.0


Item {
    id: root

    MediaDevices {
        id: devices
    }

    MediaPlayer {
        id: player

        audioOutput: AudioOutput {
            id: output
            device: devices.defaultAudioOutput
            volume: 1
        }
    }

    Connections {
        target: _player

        function onMediaChanged() {
            if(_player.media) {
                player.source = _player.media.path()
                playbar.play()
            }
        }
    }

    PlayBar {
        id: playbar
        duration: player.duration
        current: player.position

        onPositionChanged: function(position) {
            player.position = position
        }

        onPlayChanged: function (state) {
            if(state === PlayingState.play) {
                player.play()
            }
            else if (state === PlayingState.pause) {
                player.pause()
            }
            else {
                player.stop()
            }
        }

        onVolumeChanged: function(volume) {
            output.volume = volume
        }

        width: root.width
    }
}
