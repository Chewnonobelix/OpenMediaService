import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
	Connections {
		target: _image

		function onPlay(path) {
			_display.source = "file:///"+path
		}
	}

	Image {
		id: _display
		anchors.fill: parent
	}
}
