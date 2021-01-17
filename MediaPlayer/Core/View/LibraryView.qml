import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import Qt.labs.platform 1.1

import MediaPlayer 1.0
import MediaPlayer.Components 1.0

Window {
	id: root
	flags: Qt.Dialog

	width: 400
	height: 600
	//    property Library currentLibrary: _libraries.currentLibrary

	Connections {
		target: _libraries.currentLibrary

		function onSourceDirChanged() {
			sourceDir.model = _libraries.currentLibrary.sourceDir
		}
	}

	title: _libraries.currentLibrary.name

	FolderDialog {
		id: sourceSelecter

		onAccepted: _libraries.addSourceDir(folder)
	}

	Component.onCompleted: {
		visible = true
	}

	GridLayout {
		anchors.fill: parent
		MediaLabel {
			Layout.column: 0
			Layout.row: 0
			Layout.preferredHeight: root.height * 0.10
			property string role: _libraries.currentLibrary.role.toString()
			text: "Role" + ": " + role
		}
		MediaLabel {
			Layout.column: 0
			Layout.row: 1
			Layout.preferredHeight: root.height * 0.10
			text: "Last update" + ": " + _libraries.currentLibrary.lastUpdate
		}
		MediaLabel {
			Layout.column: 0
			Layout.row: 2
			Layout.preferredHeight: root.height * 0.10
			text: "Media count" + ": " + _libraries.currentLibrary.mediaCount
		}
		MediaLabel {
			Layout.column: 0
			Layout.row: 3
			Layout.preferredHeight: root.height * 0.10
			text: "Playlist count" + ": " + _libraries.currentLibrary.playlistCount
		}

		ToolButton {
			Layout.row: 4
			Layout.column: 1
			text: "+"
			onClicked: sourceSelecter.open()
		}
		ToolButton {
			Layout.row: 5
			Layout.column: 1
			text: "-"
			enabled: sourceDir.currentIndex > -1
			onClicked: _libraries.removeSourceDir(sourceDir.currentText)
		}

		ToolButton {
			Layout.row: 6
			Layout.column: 1
			text: "Scan" + " (" + _libraries.currentLibrary.probe.current + "%)"
			enabled: ! _libraries.currentLibrary.probe.isRunning
			onClicked: _libraries.currentLibrary.scan()
		}

		ListView {
			id: sourceDir
			Layout.column: 0
			Layout.row: 4
			Layout.rowSpan: 6
			Layout.preferredHeight: root.height
			Layout.preferredWidth: root.width * 0.75
			header: Label{
				text: "source directories (last probed: " + Qt.formatDateTime(_libraries.currentLibrary.lastProbed, "dd-MM-yyyy hh:mm:ss") + ")"
			}

			model: _libraries.currentLibrary.sourceDir
			readonly property string currentText: currentIndex !== -1 ? model[currentIndex] : ""

			highlight: Rectangle {
				color: "lightblue"
			}

			clip:true
			delegate: MediaListItem{
				height: sourceDir.height * 0.10
				width: sourceDir.width
				text: modelData
			}
		}
	}
}
