import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root


    property int repeatState: RepeatState.no
    property int playState: PlayingState.stop
    property int shuffleState: ShuffleState.real

    signal playChanged(int state)
    signal shuffleChanged(int state)
    signal repeatChanged(int state)

    signal nextChanged()
    signal previousChanged()

    signal backwardChanged()
    signal forwardChanged()

    signal volumeChanged(real volume)
    signal positionChanged(int position)

    property int duration
    property int current

    onCurrentChanged: progress.value = current
    GridLayout {
        anchors.fill: parent
        rows: 2

        Slider {
            id: progress
            Layout.row: 0
            Layout.column: 0
            Layout.columnSpan: 9
            Layout.fillWidth: true
            value: 0
            from: 0
            to: duration
            stepSize: 1
            onMoved: root.positionChanged(value)
        }

        MediaButton {
            id: previous
            Layout.row: 1
            Layout.column: 0
            icon.source: "qrc:/icons/previous.png"

            onClicked: root.previousChanged()

            Layout.preferredWidth: root.width * 0.05
        }

        MediaButton {
            id: backward
            Layout.column: 1
            Layout.row: 1
            icon.source: "qrc:/icons/backward.png"

            onClicked: root.backwardChanged()
            Layout.preferredWidth: root.width * 0.05
        }

        MediaButton {
            id: stop
            Layout.row: 1
            Layout.column: 2

            display: AbstractButton.IconOnly
            icon.source: "qrc:/icons/stop.png"

            onClicked: {
                playState = PlayingState.stop
                root.playChanged(playState)
            }
            Layout.preferredWidth: root.width * 0.05
        }

        MediaButton {
            id: play
            Layout.row: 1
            Layout.column: 3

            display: AbstractButton.IconOnly
            icon.source: playState === PlayingState.play ? "qrc:/icons/pause.png" : "qrc:/icons/play.png"

            onClicked: {
                playState = PlayingState.next(playState)
                root.playChanged(playState)
            }
            Layout.preferredWidth: root.width * 0.05
        }

        MediaButton {
            id: forward
            Layout.column: 4
            Layout.row: 1
            icon.source: "qrc:/icons/forward.png"

            onClicked: root.forwardChanged()
            Layout.preferredWidth: root.width * 0.05
        }

        MediaButton {
            id: next
            Layout.row: 1
            Layout.column: 5
            icon.source: "qrc:/icons/next.png"

            onClicked: root.nextChanged()
            Layout.preferredWidth: root.width * 0.05
        }

        MediaButton {
            id: repeat
            Layout.row: 1
            Layout.column: 6

            display: AbstractButton.IconOnly

            icon.source: repeatState === RepeatState.all ? "qrc:/icons/repeat.png" : repeatState === RepeatState.one ? "qrc:/icons/repeat_one.png" : "qrc:/icons/play.png"

            onClicked: {
                repeatState = RepeatState.next(repeatState)
                root.repeatChanged(repeatState)
            }
            Layout.preferredWidth: root.width * 0.05
        }

        MediaButton {
            id: suffle
            Layout.row: 1
            Layout.column: 7
            display: AbstractButton.IconOnly
            icon.source: shuffleState === ShuffleState.random ? "qrc:/icons/shuffle.png" : "qrc:/icons/play.png"

            onClicked: {
                shuffleState = ShuffleState.next(shuffleState)
                root.suffleChanged(shuffleState)
            }
            Layout.preferredWidth: root.width * 0.05
        }

        Slider {
            id: volume
            Layout.fillWidth: true
            Layout.row: 1
            Layout.column: 8
            value: 100
            from: 0
            to: 1
            stepSize: 0.1

            onMoved: {
                root.volumeChanged(value)
            }
        }
    }
}
