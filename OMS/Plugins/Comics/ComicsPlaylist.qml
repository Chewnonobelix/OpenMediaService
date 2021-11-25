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

            onCurrentIndexChanged: gridStack.currentIndex = currentIndex
        }

        StackLayout {
            id: stack
            currentIndex: typeCombo.currentIndex
            PlaylistList {
                model: _playlistListModel
            }
            GridView {
                id: gridStack
                model: _comicsPlayList

                delegate: ItemDelegate {
                    text: name

                    onClicked: {
                        unstackGrid.model = list
                        stack.currentIndex = typeCombo.count
                    }
                }
            }

            GridView {
                id: unstackGrid

                delegate: ItemDelegate {
                    text: modelData.paths[0]

                    onDoubleClicked: _comicsPlayList.play(modelData)
                }
            }
        }
    }
}
