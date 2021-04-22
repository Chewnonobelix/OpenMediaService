import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root

	Rectangle {
		anchors.fill: parent
		color: "black"
	}

	Connections {
		target: _image

		function onPlay(path) {
            display.source = "file:///"+path
		}
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
	}
}
