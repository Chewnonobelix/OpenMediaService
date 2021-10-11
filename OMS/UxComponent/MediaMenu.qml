import QtQuick 2.15
import QtQuick.Controls 2.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0

Menu {
    id: root

    signal remove()

    property Media media

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
            model: _librariesModel.at(_librariesModel.currentIndex) ? _librariesModel.at(_librariesModel.currentIndex).playlistList() : nullptr
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
        }

        Repeater {
            model: _librariesModel.at(_librariesModel.currentIndex).tag

            MenuItem {
                text: modelData
                checkable: true
                checked: media ? media.hasTag(modelData) : false

                onClicked: media.setTag(modelData)
            }
        }
    }
}
