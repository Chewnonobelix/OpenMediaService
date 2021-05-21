import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels
import MediaPlayer.Components 1.0

Item {
    id: root
    HorizontalHeaderView {
        id: header
        height: root.height * .10
        width: root.width
        syncView: table

        delegate: MediaLabel {
            text: display

            background: Rectangle {
                color: "black"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _imageListModel.sort(column)
                    console.log(table.rows)
                }
            }
        }
    }
    TableView {
        id: table
        property int firstRow: 0

        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.NoButton

            onWheel: function(wheel) {
                if(wheel.angleDelta.y < 0 )
                    table.firstRow++
                else
                    table.firstRow--

                table.firstRow = Math.max(0, table.firstRow)
                table.firstRow = Math.min(table.rows, table.firstRow)
                table.positionViewAtRow(table.firstRow, Qt.AlignCenter)
            }
        }

        anchors {
            top: header.bottom
            left: root.left
            right: root.right
            bottom: root.bottom
        }

        model: _imageListModel


        interactive: false
        columnSpacing: width * 0.001
        property var columnWidth: [width / 7, width / 7,width / 7,width / 7,width / 7,width / 7,width / 7]
        columnWidthProvider: function(column) {
            return columnWidth[column]
        }

        property int currentRow: -1


        function unselectedGradient(index) {
            return index % 2 ? StyleSheet.unselected1 : StyleSheet.unselected2
        }

        DelegateChooser {
            id: chooser
            role: "type"
            DelegateChoice {
                column: 5
                Rectangle {
                    gradient: row === table.currentRow ? StyleSheet.selected : table.unselectedGradient(row)

                    Rating {
                        z:1
                        rating: display
                        anchors.fill: parent
                        onRatingChanged: {
                            display = rating
                        }
                    }
                }
            }

            DelegateChoice {
                MediaLabel {
                    text:  display
                    clip: true
                    horizontalAlignment: Qt.AlignLeft

                    anchors {
                        leftMargin: 2
                        rightMargin: 2
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        propagateComposedEvents: true
                        onClicked: table.currentRow = row

                        onDoubleClicked: _imageListModel.play(index)
                    }

                    background: Rectangle {
                        gradient: row === table.currentRow ? StyleSheet.selected : table.unselectedGradient(row)
                    }
                }
            }
        }

        delegate: chooser
    }
}
