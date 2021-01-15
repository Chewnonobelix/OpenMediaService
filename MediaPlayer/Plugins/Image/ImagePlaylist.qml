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

	delegate: Label {
			text: display

			MouseArea {
				anchors.fill: parent

				onClicked: _imageModel.currentIndex = row
			}
	}
}
