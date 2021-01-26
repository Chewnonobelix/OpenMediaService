import QtQuick 2.15
import QtQuick.Controls 2.15

import MediaPlayer.Components 1.0

TableView {
	id: root
	model: _imageModel

	HorizontalHeaderView {
		width: root.width
		height: root.height * .20
		model: ["Path", "Count"]

		delegate: Label {
			text: modelData
		}
	}

	delegate:Rectangle {
		color: row === _imageModel.currentIndex ? "lightblue" : "#303030"
		clip: true

		height: root.height * .10
		width: root.width * .30

		MediaLabel {
			text: display
			anchors.fill: parent

			MouseArea {
				anchors.fill: parent
				onClicked: _imageModel.currentIndex = row
			}
		}
	}
}
