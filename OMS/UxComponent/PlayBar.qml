import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root


    property int repeatState: RepeatState.no
    property int playState: PlayingState.pause
    property int shuffleState: ShuffleState.realOrder

    signal playChanged(int state)
    signal shuffleChanged(int state)
    signal repeatChanged(int state)

    signal nextChanged()
    signal previousChanged()

    signal backwardChanged()
    signal forwardChanged()

    signal volumeChanged(real volume)
    signal positionChanged(int position)

    property int duration: 0
    property int current: 0

    Component.onCompleted: display()

    onCurrentChanged: {
        progress.value = current
        display()
    }

    onDurationChanged:  display()

    function display () {
        displayTime.text = progress.formatJ(current) + " / " +progress.formatJ(duration)
    }

    function play() {
        playState = PlayingState.play
        playChanged(playState)
    }

    GridLayout {
        anchors.fill: parent
        rows: 2

        Label {
            id: displayTime
            Layout.row: 0
            Layout.column: 10
            Layout.columnSpan: 1
            fontSizeMode: Text.Fit
            Layout.preferredWidth: root.width * 0.15
        }

        Slider {
            id: progress
            Layout.row: 0
            Layout.column: 0
            Layout.columnSpan: 10
            Layout.fillWidth: true
            value: 0
            from: 0
            to: duration
            stepSize: 1
            snapMode: Slider.SnapAlways
            onMoved: root.positionChanged(value)

            function formatMs(value) {
                var ms = value % 1000

                return [ms === 0 ? "" : ms+"" ,(value - ms) / 1000, ms]
            }

            function formatS(value) {
                var ms = formatMs(value)
                var s = ms[1] % 60

                return [(s+"s ")+ms[0] ,(ms[1]-s)/60, ms]
            }

            function formatM(value) {
                var s = formatS(value)
                var m = s[1] % 60

                return [(m+"m ")+s[0] ,(s[1]-m)/60 ,s]
            }

            function formatH(value) {
                var m = formatM(value)
                var h = m[1] % 24

                return [(h === 0 ? "" : h+"h ")+m[0] ,(m[1]-h)/24 ,m]
            }

            function formatJ(value) {
                var h = formatH(value)
                var j = h[1]

                return (j === 0 ? "" : j+"j ")+h[0]
            }

            ToolTip {
                visible: progress.pressed

                text: progress.formatJ(progress.value)
            }
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

            icon.source: repeatState === RepeatState.one ? "qrc:/icons/repeat_one.png" : "qrc:/icons/repeat.png"
            checked: repeatState != RepeatState.no

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
            icon.source: "qrc:/icons/shuffle.png"

            checked: shuffleState != ShuffleState.realOrder

            onClicked: {
                shuffleState = ShuffleState.next(shuffleState)
                root.shuffleChanged(shuffleState)
            }
            Layout.preferredWidth: root.width * 0.05
        }

        MediaButton {
            id: mute
            Layout.row: 1
            Layout.column: 8
            Layout.preferredWidth: root.width * 0.05
            checkable: true
            icon.source: checked ? "qrc:/icons/volume_mute.png" : "qrc:/icons/volume_up.png"

            onCheckedChanged: root.volumeChanged(checked ? 0 : volume.value)
        }

        Slider {
            id: volume
            Layout.fillWidth: true
            Layout.row: 1
            Layout.column: 9
            Layout.columnSpan: 2
            value: 100
            from: 0
            to: 1
            stepSize: 0.1

            snapMode: Slider.SnapAlways
            onMoved: {
                root.volumeChanged(value)
            }
        }
    }
}
