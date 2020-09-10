import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root

    Component.onCompleted: show()

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
                }
            }
        }
    }

    GridLayout {
        anchors.fill: parent
            ListView {
                id: libraryView
                Layout.preferredWidth: root.width * 0.20
                Layout.fillHeight: true
                Layout.row: 0
                Layout.column: 0
                Layout.rowSpan: 2
                Layout.columnSpan: 2

                model: []
                section {
                    delegate: Label {
                        text: modelData.name
                    }

                    property: "name"
                }
                delegate: ItemDelegate {
                    text: modelData.playlist

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
