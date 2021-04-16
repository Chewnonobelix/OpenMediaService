import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0


Item {
	id: root

	MouseArea {
		anchors.fill: parent
		propagateComposedEvents: true
		onClicked: function(mouse) {
			mouse.accepted = false
			root.clicked(currentLibrary)
		}
	}

	signal clicked (ControllerLibrary lib)

	SplitView.fillHeight: SplitView.view.count === 1 || SplitView.view.orientation === Qt.Horizontal
	SplitView.fillWidth: SplitView.view.count === 1 || SplitView.view.orientation === Qt.Vertical
	SplitView.onFillWidthChanged: {
		if(!SplitView.fillWidth)
			SplitView.preferredWidth = SplitView.view.width / SplitView.view.count
	}

	SplitView.onFillHeightChanged: {
		if(!SplitView.fillHeight)
			SplitView.preferredHeight = SplitView.view.height / SplitView.view.count
	}

	property ControllerLibrary currentLibrary: viewRep.itemAt(0).model

	onCurrentLibraryChanged: root.clicked(currentLibrary)
	ColumnLayout {
		anchors.fill: parent

		TabBar {
			id: viewBar

			Layout.fillWidth: true
			Layout.preferredHeight: root.height * 0.10

			Component.onCompleted: {
				currentIndex = 0
			}

			onCurrentIndexChanged: {
				if(viewRep.itemAt(currentIndex))
					currentLibrary = viewRep.itemAt(currentIndex).model
			}

			Repeater {
				id: tabRepeater
				model: 1

				MediaTabButton {
					text: qsTr("Tab ") + modelData
					onClicked: {
					}
				}
			}

			MediaTabButton {
				text: "+"

				onClicked:  {
					tabRepeater.model = viewBar.currentIndex + 1
					viewBar.currentIndex = viewBar.currentIndex - 1
                    viewRep.model.addTab()
				}
			}
		}

		StackLayout {
			id: view
			currentIndex: viewBar.currentIndex
			Layout.fillWidth: true
			Layout.fillHeight: true

			clip: true

			onCurrentIndexChanged: {
				if(viewRep.itemAt(currentIndex))
					console.log("Changed index", viewRep.itemAt(currentIndex).model.id)
			}

			Repeater {
				id: viewRep
				model: TabManager {

				}

				Loader {
					id: _playerLoader
					active: false
				}
			}
		}
	}
}
