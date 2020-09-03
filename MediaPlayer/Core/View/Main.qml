import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root

    GridLayout {
        anchors.fill: parent

        ListView {
            id: libraryView
            Layout.preferredWidth: root.width * 0.20
            Layout.fillHeight: true
            Layout.row: 0
            Layout.column: 0
            Layout.rowSpan: 2

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

        TabBar {
            id: viewBar

            Layout.fillWidth: true
            Layout.preferredHeight: root.height * 0.10
            Layout.row: 0
            Layout.column: 1

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
            Layout.column: 1

            Rectangle {
                color: "green"
            }
        }

    }

}
