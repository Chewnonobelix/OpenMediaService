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

    signal volumeChanged(int volume)
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
            value: 0
            from: 0
            to: duration

            onMoved: root.positionChanged(value)
        }

        MediaButton {
            id: previous
            Layout.row: 1
            Layout.column: 0
            icon.source: "qrc:/icons/previous.png"

            onClicked: root.previousChanged()
        }

        MediaButton {
            id: backward
            Layout.column: 1
            Layout.row: 1
            icon.source: "qrc:/icons/backward.png"

            onClicked: root.backwardChanged()
        }

        MediaButton {
            id: play
            Layout.row: 1
            Layout.column: 2

            display: AbstractButton.IconOnly
            icon.source: playState === PlayingState.play ? "qrc:/icons/stop.png" : "qrc:/icons/play.png"

            onClicked: {
                playState = PlayingState.next(playState)
                root.playChanged(playState)
            }
        }

        MediaButton {
            id: forward
            Layout.column: 3
            Layout.row: 1
            icon.source: "qrc:/icons/forward.png"

            onClicked: root.forwardChanged()
        }

        MediaButton {
            id: next
            Layout.row: 1
            Layout.column: 4
            icon.source: "qrc:/icons/next.png"

            onClicked: root.nextChanged()
        }

        MediaButton {
            id: repeat
            Layout.row: 1
            Layout.column: 5

            display: AbstractButton.IconOnly

            icon.source: repeatState === RepeatState.all ? "qrc:/icons/repeat.png" : repeatState === RepeatState.one ? "qrc:/icons/repeat_one.png" : "qrc:/icons/play.png"

            onClicked: {
                repeatState = RepeatState.next(repeatState)
                root.repeatChanged(repeatState)
            }
        }

        MediaButton {
            id: suffle
            Layout.row: 1
            Layout.column: 6
            display: AbstractButton.IconOnly
            icon.source: shuffleState === ShuffleState.random ? "qrc:/icons/shuffle.png" : "qrc:/icons/play.png"

            onClicked: {
                shuffleState = ShuffleState.next(shuffleState)
                root.suffleChanged(shuffleState)
            }
        }

        Slider {
            id: volume
            Layout.fillWidth: true
            Layout.row: 1
            Layout.column: 7
        }
    }
}
