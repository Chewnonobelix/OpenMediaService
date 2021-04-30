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


	LibraryPopup {
		id: addLibraryPop
	}

    menuBar: MediaMenuBar {
        onQuit: root.close()
    }

	GridLayout {
		id: layout
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
//                splitView.currentLibrary.currentIndex = currentIndex
                if(playlist.currentIndex !== -1) {
                    playlist.currentIndex = -1
                    playlist.currentIndex = 0

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

				text: name

				onClicked: {
                    playlist.model = controller.playlist
				}

				onDoubleClicked:  {
					ListView.view.currentIndex = index
                    controller.open()
				}
			}
		}

		MediaList {
            id: playlist

			currentIndex: -1
			Layout.preferredWidth: root.width * 0.20
			Layout.fillHeight: true
			Layout.row: 2
			Layout.column: 0
			Layout.rowSpan: 1
			Layout.columnSpan: 2

			onCurrentIndexChanged:  {
				if(model)
					model.currentIndex = currentIndex
			}

			onModelChanged: {
				forceLayout()
			}

			headerPositioning: ListView.OverlayHeader
			header: Rectangle {
                height: playlist.height * 0.05
                width: playlist.width
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
                    text: "Playlist: " + (libraryView.currentIndex > -1 ? _librariesModel.at(libraryView.currentIndex).name : "")
				}
			}

			Menu {
				id: menu1
				MenuItem {
					text: "Open"
                    onClicked: drawPlay.open()
				}

				MenuItem {
					text: "Add smart playlist"
                    onClicked: splitView.currentLibrary.addPlaylist(true)
				}
				MenuItem {
					text: "Add playlist"
                    onClicked: splitView.currentLibrary.addPlaylist()
				}
				MenuItem {
					text: "Remove playlist"
				}
			}

			Menu {
				id: menu2
				MenuItem {
					text: "Add smart playlist"
                    onClicked: splitView.currentLibrary.addPlaylist(true)
				}
				MenuItem {
					text: "Add playlist"
                    onClicked: splitView.currentLibrary.addPlaylist()
				}
			}

			MouseArea {
				anchors.fill: parent
				acceptedButtons:  Qt.RightButton

				onClicked: {
                    if(playlist.indexAt(mouseX, mouseY) !== -1) {
						menu1.popup(mouseX, mouseY)
					}
					else {
						menu2.popup(mouseX, mouseY)
					}
				}
			}

			delegate: MediaListItem {
                width: playlist.width
                height: playlist.height * 0.10
				text: (smart ? "*" : "") + (name === "" ? id : name)

                onDoubleClicked:  {
                    playlist.currentIndex = index
                    drawPlay.open()
                }
			}
		}

		Drawer {
            id: drawPlay

			edge: Qt.BottomEdge
			height: root.height * .40
			width: root.width

            onOpened: {
                playLoad.sourceComponent = _librariesModel.controller(libraryView.currentIndex).playlistComponent
                playLoad.active = playLoad.sourceComponent !== null
            }

			Loader {
                id: playLoad
				anchors.fill: parent
				active: false
			}
		}

		Menu {
			id: splitMenu
			MenuItem {
				text: "Split1"
				onClicked: splitView.addNew()
			}
		}

		MouseArea {
			z: 5
			Layout.row: 0
			Layout.column: 2
			Layout.rowSpan: 3
			Layout.columnSpan: 1
			Layout.fillHeight: true
			Layout.fillWidth: true
			acceptedButtons: Qt.RightButton

			onClicked: {
				splitMenu.open()
			}


			SplitView {
				id: splitView
				anchors.fill: parent
				orientation: Qt.Horizontal

//				property ControllerLibrary currentLibrary

//                onCurrentLibraryChanged: {
//                }

//                function onClicked(lib) {
//					currentLibrary = lib
//                    if(lib) {
//                        playlist.model = lib.playlist
//                        libraryView.currentIndex = currentLibrary.currentIndex
//                    }
//				}

				property var component;
				property var sprite;

				function addNew() {
					component = Qt.createComponent("View.qml");
					if (component.status === Component.Ready)
						finishCreation();
					else
						component.statusChanged.connect(finishCreation);
				}

				function finishCreation() {
					if (component.status === Component.Ready) {
						sprite = component.createObject(this, {});
						if (sprite === null) {
							// Error Handling
							console.log("Error creating object");
						}
						else {
							addItem(sprite)
//							sprite.onClicked.connect(onClicked)
						}
					} else if (component.status === Component.Error) {
						// Error Handling
						console.log("Error loading component:", component.errorString());
					}
				}


				Component.onCompleted:  {
					addNew()
//					currentLibrary = itemAt(0).currentLibrary
//                    playlist.model = currentLibrary.playlist
                }
			}
		}
	}
}
