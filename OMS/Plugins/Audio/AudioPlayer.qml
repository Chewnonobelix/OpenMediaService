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
        source: "file:///C:\\Qt\\Perso\\OpenMediaService\\OMS\\UnitTest\\Data\\28 La bataille de Zoug Amag Zlong.mp3"
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
