import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0

ColumnLayout {
	id: root

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

	TabBar {
		id: viewBar

		Layout.fillWidth: true
		Layout.preferredHeight: root.height * 0.10

		Component.onCompleted: {
			currentIndex = 0
		}

		Repeater {
			id: tabRepeater
			model: 1

			MediaTabButton {
				text: qsTr("Tab ") + modelData
				onClicked: {
					_main.onTabChanged(modelData)
				}
			}
		}

		MediaTabButton {
			text: "+"

			onClicked:  {
				tabRepeater.model = viewBar.currentIndex + 1
				viewBar.currentIndex = viewBar.currentIndex - 1
				_main.addTab()
			}
		}
	}

	StackLayout {
		id: view
		currentIndex: viewBar.currentIndex
		Layout.fillWidth: true
		Layout.fillHeight: true

		clip: true
		Connections {
			target: _main

			function onPlayerDisplay(name, tab) {
				var it = viewRep.itemAt(tab)

				it.source = name
				it.active = name !== ""
			}
		}

		Repeater {
			id: viewRep
			model: tabRepeater.model
			Loader {
				id: _playerLoader
				active: false
			}
		}
	}
}
