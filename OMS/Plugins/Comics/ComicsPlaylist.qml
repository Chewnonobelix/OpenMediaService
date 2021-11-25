import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MediaPlayer.Components 1.0

Item {
    ColumnLayout {
        anchors.fill: parent
        MediaCombobox {
            id: typeCombo
            model: ["Column", "Grid"]
        }

        StackLayout {
            currentIndex: typeCombo.currentIndex
            PlaylistList {
                model: _playlistListModel
            }
            GridView {
                id: grid
                model: _comicsPlayList

                delegate: ItemDelegate {
                    text: name

                    onClicked: console.log(grid.count, _comicsPlayList.rowCount())
                }
            }
        }
    }
}
