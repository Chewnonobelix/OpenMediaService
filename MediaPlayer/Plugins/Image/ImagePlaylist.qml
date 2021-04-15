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
				model: ["Library"]

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
        height: root.height * .90
		StackView {
            anchors.fill: parent
						implicitWidth: width
						implicitHeight: height

			ImageLibrairyPlaylist {
                id: _libView
								anchors.fill: parent
			}
		}
	}
}
