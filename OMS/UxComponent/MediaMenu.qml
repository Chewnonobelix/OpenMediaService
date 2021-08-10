import QtQuick 2.15
import QtQuick.Controls 2.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0

Menu {
    id: root

    signal remove()

    property Media media

    MenuItem {
        text: "Remove media"

        onClicked: root.remove()
    }

    Menu {
        title: "Add to playlist"
        MenuItem {
            text: "Add to new playlist"

            onClicked:  {
                var ret = _librariesModel.controller(_librariesModel.currentIndex).addPlaylist(false)
                _librariesModel.at(_librariesModel.currentIndex).addToPlaylist(ret, media)
            }
        }

        onOpened: rep.model =  _librariesModel.at(_librariesModel.currentIndex).playlistList()
        Repeater {
            id: rep
            model: _librariesModel.at(_librariesModel.currentIndex).playlistList()

            MenuItem {
                text: modelData.name !== "" ? modelData.name : modelData.id

                onClicked: modelData.append(media)
            }
        }
    }
}
