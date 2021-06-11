import QtQuick 2.15
import QtQuick.Controls 2.15

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
            console.log("Wesh")
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
            console.log(_settings.value("Image/Ratio"))
            console.log(_settings.value("Image/Width"))
            console.log(_settings.value("Image/Height"))
            console.log(display.sourceSize)
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
    }
}
