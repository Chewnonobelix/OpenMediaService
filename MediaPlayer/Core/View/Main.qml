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

			MediaTextEdit {
				id: libraryName
				width: addLibraryPop.width* 0.40

				validator: RegularExpressionValidator {
					regularExpression : /.+/
				}
			}

			MediaCombobox {
				id: libraryType

				model: CoreModel.typeModel
				textRole: "name"
				valueRole: "role"
			}

			MediaButton {
				Layout.preferredHeight: addLibraryPop.height * .95
				Layout.preferredWidth: addLibraryPop.width * .19
				enabled: libraryName.acceptableInput
				text: "Add"
				onClicked: {
					_db.createLibrary(libraryName.text, libraryType.currentValue)
				}
			}
			MediaButton {
				Layout.preferredHeight: addLibraryPop.height * .95
				Layout.preferredWidth: addLibraryPop.width * .19
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
		columnSpacing: root.width * 0.01
		rowSpacing: root.height * 0.01

		MediaButton {
			Layout.row: 0
			Layout.column: 0
			Layout.rowSpan: 1
			Layout.columnSpan: 1
			Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
			Layout.preferredWidth: root.width * .09
			Layout.preferredHeight: root.height * .05
			Layout.rightMargin: 0
			text: qsTr("Add")

			onClicked: addLibraryPop.open()
		}

		MediaButton {
			Layout.row: 0
			Layout.column: 1
			Layout.rowSpan: 1
			Layout.columnSpan: 1
			Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
			Layout.preferredWidth: root.width * .09
			Layout.preferredHeight: root.height * .05
			Layout.leftMargin: 0
			text: qsTr("Remove")

			enabled: libraryView.currentIndex !== -1

			onClicked: {
				_db.removeLibrary(_libraries.currentLibrary.id)
			}
		}

		MediaList {
			Connections {
				target: _librariesModel

				function onCurrentIndexChanged() {
					libraryView.currentIndex = libraryView.model.currentIndex
				}
			}


			id: libraryView
			currentIndex: -1
			Layout.preferredWidth: root.width * 0.20
			Layout.preferredHeight: root.height * 0.20

			Layout.row: 1
			Layout.column: 0
			Layout.rowSpan: 1
			Layout.columnSpan: 2
			model: _librariesModel


			onCurrentIndexChanged: {
				_librariesModel.currentIndex = currentIndex

				if(_playlist.currentIndex !== -1) {
					_playlist.currentIndex = -1
					_playlist.currentIndex = 0
				}
			}

			headerPositioning: ListView.OverlayHeader
			header: Rectangle {
				id: librariesHeader
				height: libraryView.height * 0.1
				width: libraryView.width
				z: 3

				MediaLabel {
					anchors.fill: parent
					text: qsTr("Libraries")

					background: Rectangle {
						gradient: Gradient {
							GradientStop {
								color: "navy"
								position: 0.0
							}
							GradientStop {
								color: "darkslateblue"
								position: 0.5
							}
							GradientStop {
								color: "deepskyblue"
								position: 1.0
							}
						}
					}
				}
			}

			section {
				delegate: MediaLabel {
					clip: true
					text: section
				}

				property: "role"
			}

			delegate: MediaListItem {
				width: libraryView.width
				height: libraryView.height * 0.10

				clip: true

				required property string name
				required property string role
				required property int index

				text: name

				onDoubleClicked:  {
					ListView.view.currentIndex = index
					_libraries.open()
				}
			}
		}

		MediaList {
			id: _playlist
			model: _playlistModel

			currentIndex: -1
			Layout.preferredWidth: root.width * 0.20
			Layout.fillHeight: true
			Layout.row: 2
			Layout.column: 0
			Layout.rowSpan: 1
			Layout.columnSpan: 2

			onCurrentIndexChanged:  {
				_playlistModel.currentIndex = currentIndex
			}

			header: MediaLabel {
				text: "Playlist: " + libraryView.currentIndex > -1 ? libraryView.currentItem.name : ""
			}

			Menu {
				id: menu1
				MenuItem {
					text: "Add smart playlist"
					onClicked: _libraries.addPlaylist(true)
				}
				MenuItem {
					text: "Add playlist"
					onClicked: _libraries.addPlaylist()
				}
				MenuItem {
					text: "Remove playlist"
				}
			}

			Menu {
				id: menu2
				MenuItem {
					text: "Add smart playlist"
					onClicked: _libraries.addPlaylist(true)
				}
				MenuItem {
					text: "Add playlist"
					onClicked: _libraries.addPlaylist()
				}
			}

			MouseArea {
				anchors.fill: parent
				acceptedButtons:  Qt.RightButton

				onClicked: {
					if(_playlist.indexAt(mouseX, mouseY) !== -1) {
						menu1.popup(mouseX, mouseY)
					}
					else {
						menu2.popup(mouseX, mouseY)
					}
				}
			}

			delegate: MediaListItem {
				width: _playlist.width
				height: _playlist.height * 0.10
				text: (smart ? "*" : "") + (name === "" ? id : name)
			}
		}

		Rectangle {
			id: _drawPlay

			Layout.preferredHeight: open ? root.height * .40 : 0
			Layout.fillWidth: root.width
			Layout.row: 3
			Layout.column: 0
			Layout.columnSpan: 3

			property bool open: _playlist.currentIndex !== -1

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

		TabBar {
			id: viewBar

			Layout.fillWidth: true
			Layout.preferredHeight: root.height * 0.10
			Layout.row: 0
			Layout.column: 2

			MediaTabButton {
				text: qsTr("View1")
			}
			MediaTabButton {
				text: "+"
			}
		}

		StackLayout {
			id: view
			currentIndex: viewBar.currentIndex
			Layout.fillWidth: true
			Layout.fillHeight: true
			//			Layout.preferredHeight: root.height * 0.80
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
