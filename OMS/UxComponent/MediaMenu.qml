import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0

Menu {
    id: root

    signal remove()
    signal update()

    property Media media

    onOpened: {
        tagRepeater.model = _librariesModel.at(_librariesModel.currentIndex).tag
    }

    MenuItem {
        text: qsTr("Properties")
    }

    MenuItem {
        text: qsTr("Remove media")

        onClicked: root.remove()
    }

    Menu {
        title: qsTr("Add to playlist")
        MenuItem {
            text: qsTr("Add to new playlist")

            onClicked:  {
                var ret = _librariesModel.controller(_librariesModel.currentIndex).addPlaylist(false)
                _librariesModel.at(_librariesModel.currentIndex).addToPlaylist(ret, media)
            }
        }

        onOpened: rep.model =  _librariesModel.at(_librariesModel.currentIndex).playlistList()
        Repeater {
            id: rep
            model: _librariesModel.at(_librariesModel.currentIndex) ? _librariesModel.at(_librariesModel.currentIndex).playlistList() : null
            MenuItem {
                text: modelData.name !== "" ? modelData.name : modelData.id

                onClicked: modelData.append(media)
            }
        }
    }

    Menu {
        title: qsTr("Tag")

        MenuItem {
            text: qsTr("New tag")

            onClicked: popTag.open()

            Popup {
                id: popTag

                onOpened: {
                    addTag.clear()
                }

                onClosed: {
                    if(addTag.text !== "") {
                        _librariesModel.at(_librariesModel.currentIndex).setTag(addTag.text)
                        media.setTag(addTag.text)
                    }
                }

                GridLayout {
                    anchors.fill: parent
                    columns: 2
                    rows: 2
                    MediaTextEdit {
                        id: addTag
                        Layout.columnSpan: 2
                    }

                    MediaButton {
                        text: qsTr("Add")
                        onClicked: popTag.close()
                    }

                    MediaButton {
                        text: qsTr("Cancel")

                        onClicked: {
                            addTag.clear()
                            popTag.close()
                        }
                    }
                }
            }
        }

        Repeater {
            id: tagRepeater

            MenuItem {
                text: modelData
                checkable: true
                checked: media ? media.hasTag(modelData) : false

                onClicked: media.setTag(modelData)

                Menu {
                    MenuItem {
                        text: qsTr("Remove")
                    }

                    MenuItem {
                        text: qsTr("Edit")
                    }
                }
            }
        }
    }

    Menu {
        title: qsTr("Rating")
        Repeater {
            model: 10

            MenuItem {
                onClicked: {
                    media.rating = rat.rating
                }

                Rating {
                    id: rat
                    anchors.fill: parent
                    editable: false
                    rating: modelData
                }
            }
        }
    }
}


