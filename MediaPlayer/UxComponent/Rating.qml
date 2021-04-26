import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property int rating: 0

    MouseArea {
        z:10
        anchors.fill: parent
        acceptedButtons: Qt.NoButton
        cursorShape: Qt.SizeHorCursor
    }

    Row {
        id: row

        anchors {
            fill:parent
        }

        Repeater {
            model: Math.floor(rating/2)
            Label {
                text: "F"
            }
        }
        Label {
            visible: rating%2 === 1
            text: "H"
        }
        Repeater {
            model: Math.floor((10 - rating)/2)
            Label {
                text: "E"
            }
        }
    }

    Slider{
        from: 0
        to: 10
        value: rating

        anchors {
            fill:parent
        }

        handle: Rectangle {}
        background: Rectangle {color: "transparent"}
        onValueChanged: rating = value
    }
}
