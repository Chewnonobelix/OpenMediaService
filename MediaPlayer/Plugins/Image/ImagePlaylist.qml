import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer.Components 1.0

Item {
	id: root

	MediaBackground {
		id: toolbar
		anchors {
			left: root.left
			top: root.top
		}
		width: root.width
		height: root.height * .10
		RowLayout {
			anchors.fill: parent

			MediaCombobox {
				model: ["Librairy"]

				Layout.preferredHeight: toolbar.height
			}


			StackLayout {
				Layout.preferredHeight: toolbar.height
				id: playLayout
				MediaButton {
					text: "play"

					onClicked:  {
						_image.playing()
						playLayout.currentIndex = 1
					}
				}
				MediaButton {
					text: "stop"

					onClicked:{
						_image.stop()
						playLayout.currentIndex = 0
					}
				}
			}
			MediaCheckbox {
				text: "random"
				Layout.preferredHeight: toolbar.height
			}
		}
	}
	MediaBackground {
		anchors {
			top: toolbar.bottom
			left: root.left
			bottom: root.bottom
		}
		width: root.width
		StackView {
			anchors.fill: parent
			ImageLibrairyPlaylist {
				anchors.fill: parent
			}
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
