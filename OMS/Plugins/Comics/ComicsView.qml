import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MediaPlayer.Components 1.0

Item {
    id: root
    property int index: -1
    property double zoom: 1

    onZoomChanged: {
        if(zoom < 0.5) {
            zoom = 0.5
        }
        else if(zoom > 3) {
            zoom = 3
        }
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton
        z: 1
        onWheel: function(wheel) {
            if(wheel.modifiers === Qt.ControlModifier) {
                if(wheel.angleDelta.y > 0) {
                    zoom += 0.5
                }
                else {
                    zoom -= 0.5
                }
            }
            else if(wheel.angleDelta.y > 0 && !_settings.value("Comics/rightToLeft") && !_player.rightToLeft) {
                _player.previous()
            }
            else {
                _player.next()
            }
        }
    }

    ScrollView {
        anchors.fill: parent
        contentHeight: root.height * zoom
        contentWidth: root.width * zoom
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOn

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
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }
    MouseArea {
        anchors{
            top: root.top
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
            text: (_player.currentPage + 1) + "/" + _player.pageCount + " (x"+zoom+")"
        }
    }
}
