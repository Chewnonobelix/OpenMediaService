import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MediaPlayer.Components 1.0

Item {
    id: root
    property int index: -1

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton

        onWheel: function(wheel) {
            if(wheel.angleDelta.y > 0) {
                _player.previous()
            }
            else if(wheel.angleDelta.y < 0) {
                _player.next()
            }
        }
    }

    StackLayout{
        id: layout
        anchors.fill: parent
        currentIndex: _player.currentPage

        Repeater {
            id: rep
            model: _player
            Image {
                id: display
                source: "file:///"+page
            }
        }
    }

    MouseArea {
        anchors{
            bottom: root.bottom
            left: root.left
        }

        width: root.width
        height: root.height * .10
        hoverEnabled: true

        ComicsPreview {
            id: preview
            visible: parent.containsMouse
            anchors.fill: parent
        }
    }

    Rectangle {
        anchors {
            top: parent.top
            right: parent.right
        }

        width: parent.width * .05
        height: parent.height * 0.05

        color: "transparent";
        MediaLabel {
            anchors.fill: parent
            text: (_player.currentPage + 1) + "/" + _player.pageCount
        }
    }
}
