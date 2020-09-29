import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0

ApplicationWindow {
    id: root

    Component.onCompleted: {
        //        _main.onAddLibrary()
        show()
    }

    width: 600
    height: 400
    Popup {
        id: addLibraryPop

        GridLayout {
            anchors.fill: parent
            rows: 2
            TextField {
                id: libraryName
            }

            ComboBox {
                id: libraryType

                onDownChanged: console.log(CoreModel.typeModel.count)
                model: CoreModel.typeModel
                textRole: "name"
                valueRole: "role"
            }

            Button {
                text: "Add"
                onClicked: {
                    console.log(libraryName.text, libraryType.currentValue)
                    _db.createLibrary(libraryName.text, libraryType.currentValue)
                }
            }
            Button {
                text: "Close"
                onClicked: {
                    addLibraryPop.close()
                    _main.onAddLibrary()
                }
            }
        }
    }

    GridLayout {
        anchors.fill: parent
        //        Connections {
        //            target: _main

        //            function onLibraryModelChanged(model) {
        //                libraryView.model = model
        //            }
        //        }
        ListView {
            id: libraryView
            Layout.preferredWidth: root.width * 0.20
            Layout.fillHeight: true
            Layout.row: 0
            Layout.column: 0
            Layout.rowSpan: 2
            Layout.columnSpan: 2
            model: _libraryModel

            property Library currentModel: null

            onCurrentIndexChanged: {
                currentModel = model.at(currentIndex)
            }

            section {
                delegate: Label {
                    text: section
                }

                property: "role"
            }
            delegate: Rectangle {
                color: ListView.isCurrentItem ? "lightblue" : "white"
                width: libraryView.width
                height: libraryView.height * 0.10

                required property string name
                required property string role
                required property int index
                Label {
                    anchors.fill: parent
                    text: name + " " + role
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        libraryView.currentIndex = index
                    }
                }
            }
        }

        Button {
            Layout.row: 2
            Layout.column: 0
            Layout.rowSpan: 1
            Layout.columnSpan: 1
            text: qsTr("Add")

            onClicked: addLibraryPop.open()
        }

        Button {
            Layout.row: 2
            Layout.column: 1
            Layout.rowSpan: 1
            Layout.columnSpan: 1
            text: qsTr("Remove")

            enabled: libraryView.currentIndex !== -1

            onClicked: {
                _db.removeLibrary(libraryView.currentModel.id)
            }
        }

        TabBar {
            id: viewBar

            Layout.fillWidth: true
            Layout.preferredHeight: root.height * 0.10
            Layout.row: 0
            Layout.column: 2

            TabButton {
                text: qsTr("View1")
            }
            TabButton {
                text: "+"
            }
        }

        StackLayout {
            id: view
            currentIndex: viewBar.currentIndex
            Layout.fillWidth: true

            Layout.preferredHeight: root.height * 0.80
            Layout.row: 1
            Layout.column: 2
            Layout.rowSpan: 2

            Rectangle {
                color: "Yellow"
            }
        }

    }

}
