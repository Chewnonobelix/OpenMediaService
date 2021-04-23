import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root

    property int rating: 0


    Row {
        anchors.fill: parent
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
}
