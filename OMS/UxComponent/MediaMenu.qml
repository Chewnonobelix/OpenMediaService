import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0

Menu {
    id: root

    signal remove()
    signal update()
    signal properties()

    property Media media

    onOpened: {
        tags.model = _librariesModelGlobal.controller(_librariesModelGlobal.currentIndex).tags
        tags.tagList = media.tags
    }

    MenuItem {
        text: qsTr("Properties")

        onClicked: root.properties()
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
                var ret = _librariesModelGlobal.controller(_librariesModelGlobal.currentIndex).addPlaylist(false)
                _librariesModelGlobal.at(_librariesModelGlobal.currentIndex).addToPlaylist(ret, media.id)
            }
        }

        onOpened: rep.model =  _librariesModelGlobal.at(_librariesModelGlobal.currentIndex).playlistList()
        Repeater {
            id: rep
            model: _librariesModelGlobal.at(_librariesModelGlobal.currentIndex) ? _librariesModelGlobal.at(_librariesModelGlobal.currentIndex).playlistList() : null
            MenuItem {
                text: modelData.name !== "" ? modelData.name : modelData.id

                onClicked: modelData.append(media)
            }
        }
    }

    //TagMenu
    TagMenu {
        id: tags

        onAddTag: function(tag) {
            media.setTag(tag)
        }

        onRemoveTag: function(tag) {
            media.setTag(tag)
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


