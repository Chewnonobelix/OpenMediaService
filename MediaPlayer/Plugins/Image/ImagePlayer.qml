import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
	Rectangle {
		anchors.fill: parent
		color: "black"
	}

	Connections {
		target: _image

		function onPlay(path) {
			_display.source = "file:///"+path
		}
	}

	MouseArea {
		anchors.fill: parent
		acceptedButtons: Qt.NoButton

		onWheel: {
			console.log(wheel.angleDelta)
			if(wheel.angleDelta.y > 0) {
				_imageModel.currentIndex = _imageModel.currentIndex-1
			}
			if(wheel.angleDelta.y < 0) {
				_imageModel.currentIndex = _imageModel.currentIndex+1
			}

		}
	}

	Image {
		id: _display
		anchors.fill: parent
		fillMode: Image.PreserveAspectFit
	}
}
