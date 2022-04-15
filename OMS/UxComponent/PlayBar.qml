import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root


    property int repeatState: RepeatState.no
    property int playState: PlayingState.stop
    property int shuffleState: ShuffleState.real

    GridLayout {
        anchors.fill: parent

        MediaButton {
            id: repeat

            display: AbstractButton.IconOnly

            icon.source: repeatState === RepeatState.all ? "qrc:/icons/repeat.png" : repeatState === RepeatState.one ? "qrc:/icons/repeat_one.png" : "qrc:/icons/play.png"

            onClicked: {
                repeatState = RepeatState.next(repeatState)
            }
        }

        MediaButton {
            id: play

            display: AbstractButton.IconOnly
            icon.source: playState === PlayingState.stop ? "qrc:/icons/stop.png" : "qrc:/icons/play.png"

            onClicked: {
                playState = PlayingState.next(playState)
            }

        }

        MediaButton {
            id: suffle
            display: AbstractButton.IconOnly
            icon.source: shuffleState === ShuffleState.random ? "qrc:/icons/shuffle.png" : "qrc:/icons/play.png"

            onClicked: {
                shuffleState = ShuffleState.next(shuffleState)
            }
        }

    }
}
