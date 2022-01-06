import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels
import QtQuick.Layouts 1.15

import MediaPlayer.Model 1.0

Item {
    id: root

    property PlaylistListModel model

    Menu {
        height: 175

        id: columnMenu

        ListView {
            model: root.model.columnList()
            anchors.fill: parent

            delegate: Item {
                height: columnMenu.height * 0.10
                Row {
                    anchors.fill: parent
                    MediaCheckbox {
                        checked: root.model.columnEnable(modelData)
                        height: parent.height

                        onClicked: root.model.setColumnEnable(modelData, checked)
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
                        root.model.setColumnWidth(column, mouseX)
                        table.forceLayout()
                    }
                }
                onClicked: function(mouse){
                    if(mouse.button === Qt.LeftButton) {
                        root.model.sort(column)
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

        Component.onCompleted: root.model.width = width

        interactive: false
        reuseItems: false

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

        model: root.model

        clip: true
        Connections {
            target: table

            function onWidthChanged() {
                root.model.width = table.width
            }
        }

        columnSpacing: width * 0.001

        columnWidthProvider: function(column) { return root.model.columnWidth(column) }

        property int currentRow: -1


        function unselectedGradient(index) {
            return index % 2 ? StyleSheet.unselected1 : StyleSheet.unselected2
        }

        DelegateChooser {
            id: chooser
            role: "type"
            DelegateChoice {
                column: root.model.columnOf("rating")
                Rectangle {
                    gradient: row === table.currentRow ? StyleSheet.selected : table.unselectedGradient(row)

                    Rating {
                        z:1
                        rating: display
                        anchors.fill: parent

                        onActivated: (rating) => {
                            display = rating
                        }
                    }
                }
            }

            DelegateChoice {
                MediaLabel {

                    text: display
                    clip: true
                    horizontalAlignment: Qt.AlignLeft

                    anchors {
                        leftMargin: 2
                        rightMargin: 2
                    }

                    MediaMenu {
                        id: mediaMenu

                        media: pointer

                        onProperties: root.model.displayProperties(row)
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
                            root.model.play(index)
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
