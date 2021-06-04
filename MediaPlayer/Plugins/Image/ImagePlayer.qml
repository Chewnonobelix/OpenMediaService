import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root

    Connections {
        target: _image

        function onPlay(m) {
            display.source = "file:///"+m
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
            console.log("wheel")
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
