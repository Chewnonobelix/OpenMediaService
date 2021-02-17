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
				Layout.preferredHeight: addLibraryPop.height * .5
				Layout.preferredWidth: addLibraryPop.width * .19
				enabled: libraryName.acceptableInput
				text: "Add"
				onClicked: {
					_db.createLibrary(libraryName.text, libraryType.currentValue)
					addLibraryPop.close()
				}
			}
			MediaButton {
				Layout.preferredHeight: addLibraryPop.height * .5
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

				lock: true
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


			headerPositioning: ListView.OverlayHeader
			header: Rectangle {
				height: _playlist.height * 0.05
				width: _playlist.width
				z:3
				gradient: Gradient {
					GradientStop {
						color: "darkred"
						position: 0.0
					}
					GradientStop {
						color: "orangered"
						position: 1.0
					}
				}

				MediaLabel {
					id: playlistHeader
					anchors.fill: parent
					text: "Playlist: " + (libraryView.currentIndex > -1 ? libraryView.currentItem.name : "")
				}
			}

			Menu {
				id: menu1
				MenuItem {
					text: "Open"
					onClicked: _drawPlay.open()
				}

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

				onDoubleClicked: _drawPlay.open()
			}
		}

		Drawer {
			id: _drawPlay

			edge: Qt.BottomEdge
			height: root.height * .40
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

		TabBar {
			id: viewBar

			Layout.fillWidth: true
			Layout.preferredHeight: root.height * 0.10
			Layout.row: 0
			Layout.column: 2

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

			Layout.row: 1
			Layout.column: 2
			Layout.rowSpan: 2

			clip: true
			Connections {
				target: _main

				function onPlayerDisplay(name, tab) {
					var it = viewRep.itemAt(tab)
					view.currentItem.active = name !== ""
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
}
