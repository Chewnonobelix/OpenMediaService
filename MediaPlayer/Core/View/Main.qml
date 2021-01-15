import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0

ApplicationWindow {
	id: root

	Component.onCompleted: {
		show()
	}

	width: 600
	height: 400

	Shortcut {
		sequence: "Ctrl+Q"
		onActivated: root.close()
	}

	Popup {
		id: addLibraryPop

		onOpened: libraryName.clear()
		GridLayout {
			anchors.fill: parent
			rows: 2

			TextField {
				id: libraryName
				width: addLibraryPop.width* 0.40

				validator: RegularExpressionValidator {
					regularExpression : /.+/
				}
			}

			ComboBox {
				id: libraryType

				model: CoreModel.typeModel
				textRole: "name"
				valueRole: "role"
			}

			MediaButton {
				enabled: libraryName.acceptableInput
				text: "Add"
				onClicked: {
					_db.createLibrary(libraryName.text, libraryType.currentValue)
				}
			}
			MediaButton {
				text: "Close"
				onClicked: {
					addLibraryPop.close()
				}
			}
		}
	}

	Connections {
		target: _libraries
	}

	GridLayout {
		anchors.fill: parent

		Drawer {
			id: _drawPlay
			edge: Qt.TopEdge

			height: root.height * .60
			width: root.width

			Loader {
				Connections {
					target: _main

					function onPlaylistDisplay(path) {
						_playLoad.source = path
						_playLoad.active = path !== ""
					}
				}

				id: _playLoad
				anchors.fill: parent
				active: false
			}
		}

		ListView {
			id: _playlist
			model: _playlistModel

			Layout.preferredWidth: root.width * 0.20
			Layout.fillHeight: true
			Layout.row: 2
			Layout.column: 0
			Layout.rowSpan: 1
			Layout.columnSpan: 2

			onCurrentIndexChanged:  {currentIndex !== -1 ? _drawPlay.open() : _drawPlay.close()
				_playlistModel.currentIndex = currentIndex
			}
			header: Label {
				text: "Playlist: " + libraryView.currentItem.name
			}

			delegate: Label {
				text: (smart ? "*" : "") + name

				MouseArea {
					anchors.fill: parent
					onClicked: _playlist.currentIndex = _playlist.currentIndex === index ? -1 : index
				}
			}
		}

		ListView {
			Connections {
				target: _librariesModel

				function onCurrentIndexChanged() {
					libraryView.currentIndex = libraryView.model.currentIndex
				}
			}

			id: libraryView
			Layout.preferredWidth: root.width * 0.20
			Layout.preferredHeight: root.height * 0.20
			Layout.row: 1
			Layout.column: 0
			Layout.rowSpan: 1
			Layout.columnSpan: 2
			model: _librariesModel


			onCurrentIndexChanged: {
				_librariesModel.currentIndex = currentIndex
			}

			headerPositioning: ListView.OverlayHeader
			header: Rectangle {
				id: librariesHeader
				color: "lightgreen"
				height: libraryView.height * 0.1
				z: 3

				Label {
					text: qsTr("Libraries")
				}
			}

			clip: true

			section {
				delegate: Label {
					clip: true
					text: section
				}

				property: "role"
			}
			delegate: Rectangle {
				color: ListView.isCurrentItem ? "lightblue" : "white"
				width: libraryView.width
				height: libraryView.height * 0.10

				clip: true

				required property string name
				required property string role
				required property int index

				Label {
					anchors.fill: parent
					text: name
					horizontalAlignment: Qt.AlignHCenter
					verticalAlignment: Qt.AlignVCenter
				}

				MouseArea {
					anchors.fill: parent
					onClicked: {
						libraryView.currentIndex = index
					}

					onDoubleClicked: _libraries.open()
				}
			}
		}

		MediaButton {
			Layout.row: 0
			Layout.column: 0
			Layout.rowSpan: 1
			Layout.columnSpan: 1
			text: qsTr("Add")

			onClicked: addLibraryPop.open()
		}

		MediaButton {
			Layout.row: 0
			Layout.column: 1
			Layout.rowSpan: 1
			Layout.columnSpan: 1
			text: qsTr("Remove")

			enabled: libraryView.currentIndex !== -1

			onClicked: {
				_db.removeLibrary(_libraries.currentLibrary.id)
			}
		}


		TabBar {
			id: viewBar

			Layout.fillWidth: true
			Layout.preferredHeight: root.height * 0.10
			Layout.row: 0
			Layout.column: 2

			TabButton {
				text: qsTr("View1")
			}
			TabButton {
				text: "+"
			}
		}

		StackLayout {
			id: view
			currentIndex: viewBar.currentIndex
			Layout.fillWidth: true

			Layout.preferredHeight: root.height * 0.80
			Layout.row: 1
			Layout.column: 2
			Layout.rowSpan: 2

			Loader {
				id: _playerLoader
				active: false

				Connections {
					target: _main

					function onPlayerDisplay(name) {
						_playerLoader.source = name
						_playerLoader.active = name !== ""
					}
				}
			}
		}
	}
}
