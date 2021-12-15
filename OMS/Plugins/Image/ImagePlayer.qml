import QtQuick 2.15
import QtQuick.Controls 2.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0

Item {
    id: root

    function set() {
        if(_settings.value("Image/Ratio") === "Fit") {
            display.fillMode = Image.PreserveAspectFit
        }
        else if(_settings.value("Image/Ratio") === "Fill") {
            display.fillMode = Image.Stretch
        }
        else {
            display.fillMode = Image.Pad
            display.sourceSize.width = _settings.value("Image/Width")
            display.sourceSize.height = _settings.value("Image/Height")

        }

    }

    Component.onCompleted: {
        set()
    }

    Connections {
        target: _image
        function onPlay(m) {
            display.source = "file:///"+m
        }
    }

    Connections {
        target: _settings

        function onSettingsChanged() {
            set()
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton

        onWheel: function(wheel){
            if(wheel.angleDelta.y > 0) {
                _image.onCurrentIndexChanged(-1)
            }
            if(wheel.angleDelta.y < 0) {
                _image.onCurrentIndexChanged(1)
            }

        }
    }

    Image {
        id: display
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: root.parent && root.parent.media ? "file:///" + root.parent.media.paths[0] : ""

        ButtonOrder {
            id: od

            model: _image.orderModel
            positionning: ButtonOrder.AnchorType.Left
            anchors {
                right: display.right
                top: display.top
            }

            width: display.width * .075
            height: display.height * .1

            popupWidth: display.width * 0.3
            popupHeight:  display.height * 0.4
        }
    }
}
