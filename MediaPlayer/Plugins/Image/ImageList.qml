import QtQuick 2.15
import QtQuick.Controls 2.15

import MediaPlayer.Components 1.0

Item {
    id: root
    HorizontalHeaderView {
        id: header
        height: root.height * .10
        width: root.width
        syncView: table
    }
    TableView {
        id: table

        anchors {
            top: header.bottom
            left: root.left
            right: root.right
            bottom: root.bottom
        }

        model: _imageListModel

        property int currentRow: -1

        delegate: MediaLabel {
            text: display

            MouseArea {
                anchors.fill: parent

                onClicked: table.currentRow = row

                onDoubleClicked: _imageListModel.play(index)
            }

            background: Rectangle {
                property Gradient selected: Gradient {
                    GradientStop {
                        color: "black"
                        position: 0.0
                    }

                    GradientStop {
                        color: "darkblue"
                        position: 0.40
                    }

                    GradientStop {
                        color: "aqua"
                        position: 0.5
                    }

                    GradientStop {
                        color: "darkblue"
                        position: 0.60
                    }

                    GradientStop {
                        color: "black"
                        position: 1.0
                    }
                }

                property Gradient unselected: Gradient {
                    GradientStop {
                        color: row % 2 ? "grey" : Qt.lighter("grey", 0.5)
                    }
                }

                gradient: row === table.currentRow ? selected : unselected

            }
        }
    }
}
