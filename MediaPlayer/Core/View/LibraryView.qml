import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Dialogs 1.3

import MediaPlayer 1.0

Window {
    id: root
    flags: Qt.Dialog

    width: 400
    height: 600
    property Library currentLibrary: _libraries.currentLibrary

    title: currentLibrary.name

        FileDialog {
            id: sourceSelecter
            selectFolder: true

            onAccepted: _libraries.addSourceDir(fileUrl)
        }

    onCurrentLibraryChanged: sourceDir.model = currentLibrary.sourceDir
    Component.onCompleted: {
        visible = true
        currentLibrary = Qt.binding(function() {
            return _libraries.currentLibrary
        }
        )
    }
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
            id: sourceDir
            Layout.column: 0
            Layout.row: 4
            Layout.rowSpan: 6
            Layout.preferredHeight: root.height
            Layout.preferredWidth: root.width * 0.75
            header: Label{
                text: "source directories"
            }

            model: currentLibrary.sourceDir

            onCountChanged: console.log(count)
            //            model: ["dir1", "dir2"]
            clip:true
            delegate: ItemDelegate{
                height: sourceDir.height * 0.10
                width: sourceDir.width
                text: modelData
            }
        }
    }
}
