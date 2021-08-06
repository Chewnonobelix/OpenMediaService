import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels
import QtQuick.Layouts 1.15

Item {
    id: root

    Menu {
        height: 175

        id: columnMenu

        ListView {
            model: _playlistListModel.columnList()
            anchors.fill: parent

            delegate: Item {
                height: columnMenu.height * 0.10
                Row {
                    anchors.fill: parent
                    MediaCheckbox {
                        checked: _playlistListModel.columnEnable(modelData)
                        height: parent.height

                        onClicked: _playlistListModel.setColumnEnable(modelData, checked)
                    }
                    MediaLabel {
                        height: parent.height
                        text: modelData

                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                    }
                }
            }
        }
    }

    HorizontalHeaderView {
        id: header
        height: root.height * .10
        width: root.width
        syncView: table
        interactive: false

        delegate: MediaLabel {
            id: columnDisplay
            text: display

            background: Rectangle {
                color: "black"
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                pressAndHoldInterval: 50
                hoverEnabled: true
                cursorShape: mouseX > width * .95 ? Qt.SplitHCursor : Qt.ArrowCursor

                onMouseXChanged: {
                    if(pressed && cursorShape === Qt.SplitHCursor) {
                        _playlistListModel.setColumnWidth(column, mouseX)
                        table.forceLayout()
                    }
                }
                onClicked: function(mouse){
                    if(mouse.button === Qt.LeftButton) {
                        _playlistListModel.sort(column)
                    }
                    else {
                        columnMenu.x = mouse.x
                        columnMenu.y = mouse.y
                        columnMenu.open()
                    }
                }
            }
        }
    }
    TableView {
        id: table

        Component.onCompleted: _playlistListModel.width = width

        interactive: false

        ScrollBar.horizontal: ScrollBar {
        }

        ScrollBar.vertical: ScrollBar {
        }

        anchors {
            top: header.bottom
            left: root.left
            right: root.right
            bottom: root.bottom
        }

        model: _playlistListModel

        clip: true
        Connections {
            target: table

            function onWidthChanged() {
                _playlistListModel.width = table.width
            }
        }

        columnSpacing: width * 0.001

        columnWidthProvider: function(column) { return _playlistListModel.columnWidth(column) }

        property int currentRow: -1


        function unselectedGradient(index) {
            return index % 2 ? StyleSheet.unselected1 : StyleSheet.unselected2
        }

        DelegateChooser {
            id: chooser
            role: "type"
            DelegateChoice {
                column: _playlistListModel.columnOf("rating")
                Rectangle {
                    gradient: row === table.currentRow ? StyleSheet.selected : table.unselectedGradient(row)

                    Rating {
                        z:1
                        //                        Component.onCompleted: rating = display
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

                    MediaMenu {
                        id: mediaMenu
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        propagateComposedEvents: true
                        acceptedButtons: Qt.LeftButton| Qt.RightButton
                        onClicked: function(mouse) {
                            table.currentRow = row

                            if(mouse.button === Qt.RightButton) {
                                mediaMenu.x = mouseX
                                mediaMenu.y = mouseY
                                mediaMenu.open()
                            }
                        }
                        onDoubleClicked: {
                            _playlistListModel.play(index)
                        }
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
