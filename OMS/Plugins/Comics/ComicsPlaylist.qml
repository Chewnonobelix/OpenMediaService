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

            onCurrentIndexChanged: stack.currentIndex = currentIndex
        }

        MediaButton {
            text: "<-"

            visible: typeCombo.currentIndex !== 0
            onClicked: stack.currentIndex = 1
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

                clip: true
                cellWidth: height * 0.3
                cellHeight: width * 0.4

                delegate: ColumnLayout {
                    Image {
                        source: cover
                        fillMode: Image.Stretch
                        sourceSize {
                            width: gridStack.cellWidth
                            height: gridStack.cellHeight
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                unstackGrid.model = list
                                stack.currentIndex = typeCombo.count
                            }
                        }
                    }

                    MediaLabel {
                        text: name + "(" + list.length + ")"
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
