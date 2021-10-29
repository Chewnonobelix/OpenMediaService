import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MediaPlayer.Components 1.0

Item {
    property int index: -1

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton

        onWheel: function(wheel) {
            if(wheel.angleDelta.y > 0 && layout.currentIndex > 0) {
                layout.currentIndex --
            }
            else if(wheel.angleDelta.y < 0 && layout.currentIndex < rep.count - 1) {
                layout.currentIndex ++
            }
        }
    }

    StackLayout{
        id: layout
        anchors.fill: parent
        onCountChanged: currentIndex = _player.currentPage
        onCurrentIndexChanged: _player.currentPage = currentIndex
        Repeater {
            id: rep
            model: _player
            Image {
                id: display
                source: "file:///"+page
            }
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
            text: (layout.currentIndex + 1) + "/" + _player.pageCount
        }
    }
}
