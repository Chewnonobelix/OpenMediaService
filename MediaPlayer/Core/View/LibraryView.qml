import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls 2.13
import QtQuick.Dialogs 1.3

Window {
    id: root
    property var lib
    
    FileDialog {
        id: sourceDialog
        selectFolder: true
        
        title: qsTr("Select source directory")
        
        onAccepted: {
            root.lib.addSourceDir(folder)
            close()
        }
        
        onRejected: close()
    }
    
    GridLayout {
        anchors.fill: parent
        
        Label {
            Layout.row: 0
            Layout.column: 0
            text: root.lib.name
        }
        
        Label {
            Layout.row: 0
            Layout.column: 1
            text: root.lib.role
        }
        
        
        Button {
            Layout.row: 0
            Layout.column: 2
            text: qsTr("Last probed") + ": " + Qt.formatDateTime(root.lib.lastProbed, "hh:mm:ss dd-MM-yyyy")
            onClicked: root.lib.probe()
        }
        
        Rectangle {
            color: "transparent"
            border.color: "gold"
            Layout.row: 1
            Layout.column: 0
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * .30
            ListView {
                id: sourceDir
                model: root.lib.sourceDir
                anchors.fill: parent
                clip: true
                
                header: Label {
                    text: qsTr("Source directories")
                    z: 10
                }
                
                headerPositioning: ListView.OverlayHeader
                
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton
                    z:10
                    onClicked: {
                                     sourceMenu.popup(mouseX, mouseY)
                    }
                }
                Menu {
                    id: sourceMenu
                    
                    MenuItem {
                        text: qsTr("Add source")
                        onClicked: sourceDialog.open()
                    }
                    
                    MenuItem {
                        text: qsTr("Remove source")
                        visible: sourceDir.indexAt(sourceMenu.x, sourceMenu.y) !== -1
                        
                        onClicked: {
                            root.lib.removeSourceDir(sourceDir.model[sourceDir.indexAt(sourceMenu.x, sourceMenu.y)])
                        }
                    }
                }
                
                delegate: Rectangle {
                    width: sourceDir.width * .99
                    height: sourceDir.height * 0.05
                    
                    Label {
                        anchors.fill: parent
                        text: modelData
                    }
                }
            }
        }
        
        Rectangle {
            color: "transparent"
            border.color: "gold"
            Layout.row: 1
            Layout.column: 1
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * .30
            ListView {
                id: filters
                model: ["*.mp3", "*.flac"]
                anchors.fill: parent
                clip: true
                
                header: Label {
                    text: qsTr("Library's filters")
                    z: 10
                }
                
                headerPositioning: ListView.OverlayHeader
                delegate: Rectangle {
                    width: sourceDir.width * .99
                    height: sourceDir.height * 0.05
                    
                    Label {
                        anchors.fill: parent
                        text: modelData
                        MouseArea {
                            anchors.fill: parent
                            onClicked: console.log("youkou2")
                        }
                        
                        //                    horizontalAlignment: Qt.AlignHCenter
                        //                    verticalAlignment: Qt.AlignVCenter
                    }
                }
            }
        }
        
    }
}
