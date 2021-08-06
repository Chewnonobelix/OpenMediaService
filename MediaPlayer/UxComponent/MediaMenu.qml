import QtQuick 2.15
import QtQuick.Controls 2.15

Menu {
    id: root

    signal remove()

    MenuItem {
        text: "Remove media"

        onClicked: root.remove()
    }

    Menu {
        title: "Add to playlist"
        MenuItem {
            text: "Add to new playlist"

            onClicked: _librariesModel.controller(_librariesModel.currentIndex).addPlaylist(false)
        }

        Repeater {

        }
    }
}
