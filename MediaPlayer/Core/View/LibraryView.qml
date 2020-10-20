import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Dialogs 1.3

import MediaPlayer 1.0

Window {
    id: root
    flags: Qt.Dialog

    property Library currentLibrary: _libraries.currentLibrary

    title: currentLibrary.name

    FileDialog {
        id: sourceSelecter
        selectFolder: true
    }

    Component.onCompleted: visible = true
    GridLayout {
        anchors.fill: parent
        Label {
            Layout.column: 0
            Layout.row: 0
            Layout.preferredHeight: root.height * 0.10
            text: "Role" + ": " + currentLibrary.role
        }
        Label {
            Layout.column: 0
            Layout.row: 1
            Layout.preferredHeight: root.height * 0.10
            text: "Last update" + ": " + currentLibrary.lastUpdate
        }
        Label {
            Layout.column: 0
            Layout.row: 2
            Layout.preferredHeight: root.height * 0.10
            text: "Media count" + ": " + currentLibrary.mediaCount
        }
        Label {
            Layout.column: 0
            Layout.row: 3
            Layout.preferredHeight: root.height * 0.10
            text: "Playlist count" + ": "
        }

        ToolButton {
            Layout.row: 4
            Layout.column: 1
            text: "+"
            onClicked: sourceSelecter.open()
        }
        ToolButton {
            Layout.row: 5
            Layout.column: 1
            text: "-"
        }
        ToolButton {
            Layout.row: 6
            Layout.column: 1
            text: "Sync"
        }

        ListView {
            Layout.column: 0
            Layout.row: 4
            Layout.rowSpan: 6
            Layout.fillHeight: true
            header: Label{
                text: "source directories"
            }

                        model: currentLibrary.sourceDir
//            model: ["dir1", "dir2"]

            delegate: ItemDelegate{
                text: modelData
            }
        }

    }
}
