import QtQuick 2.15
import QtQuick.Controls 2.15

import MediaPlayer.Components 1.0

Frame {
	StackView {
		anchors.fill: parent
		ImageLibrairyPlaylist {
			anchors.fill: parent
		}
	}
}

//TableView {
//	id: root
//	model: _imageLibrairyModel

//	HorizontalHeaderView {
//		width: root.width
//		height: root.height * .20
//		model: ["Path", "Count"]

//		delegate: Label {
//			text: modelData
//		}
//	}

//	delegate:Rectangle {
//		color: row === _imageLibrairyModel.currentIndex ? "lightblue" : "#303030"
//		clip: true

//		height: root.height * .10
//		width: root.width * .30

//		MediaLabel {
//			text: display
//			anchors.fill: parent

//			MouseArea {
//				anchors.fill: parent
//				onClicked: _imageLibrairyModel.currentIndex = row
//			}
//		}
//	}
//}
