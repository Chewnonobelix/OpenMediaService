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
        tags.model = _librariesModel.controller(_librariesModel.currentIndex).tags
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


