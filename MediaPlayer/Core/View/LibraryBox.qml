import QtQuick 2.13
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    GridLayout {
        anchors.fill: parent
        Label {
            text: qsTr("Library")
            Layout.row: 0
            Layout.column: 0
            Layout.preferredWidth: parent.width * .2            
            Layout.preferredHeight: parent.height * .05
        }

        Label {
            text: qsTr("Playlist")
            Layout.row: 0
            Layout.column: 1             
            Layout.preferredWidth: parent.width * .2            
            Layout.preferredHeight: parent.height * .05
        }        
        
        Label {
            text: qsTr("Media")
            Layout.row: 0
            Layout.column: 2
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * .05
        }
        
        ListView {
            id: libraryView
            objectName: "libraryView"
            Layout.row: 1
            Layout.column: 0
            Layout.preferredWidth: parent.width * .2            
            Layout.fillHeight: true
            clip: true
            model: []

            section.property: "modelData.role"
            section.criteria: ViewSection.FullString
            section.delegate: Rectangle {
                color: "lightsteelblue"
                height: libraryView.height * 0.06
                width: libraryView.width
               
                
                Label {
                    anchors.fill: parent
                    text: section
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    fontSizeMode: Text.Fit
                }
            }

           
            signal s_openLibrary(string name)
            
            delegate: Rectangle {
                color: "transparent"
                height: libraryView.height * 0.04
                width: libraryView.width
                
                Label {
                    anchors.fill: parent
                    text: modelData.name
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    
                    MouseArea {
                        anchors.fill: parent
                        onDoubleClicked: {
                            libraryView.s_openLibrary(modelData.name)
                            console.log(modelData.sourceDir)
                        }
                    }
                    
                }
            }
        }
        
        ListView {
            id: playlistView
            objectName: "playlistView"
            Layout.row: 1
            Layout.column: 1             
            Layout.preferredWidth: parent.width * .2            
            Layout.fillHeight: true
            clip: true
            
            model: []

            delegate: Rectangle {
                color: "transparent"
                height: playlistView.height * 0.03
                width: playlistView.width
                

                Label {
                    anchors.fill: parent
                    text: modelData.added
                    MouseArea {
                        anchors.fill: parent
//                        onClicked: console.log(playlistView.model)
                    }
                    
                }
            }
            
        }
        
        GridView {
            id: mediaView
            objectName: "mediaView"
            Layout.row: 1
            Layout.column: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            
            model: []

            delegate: Rectangle {
                color: "transparent"
                height: playlistView.height * 0.03
                width: playlistView.width
                

                Label {
                    anchors.fill: parent
                    text: Qt.formatDate(modelData.added, "dd-MM-yyyy")
                    clip: true
                    MouseArea {
                        anchors.fill: parent
                        onClicked: console.log(modelData.paths)
//                        onClicked: console.log(playlistView.model)
                    }
                    
                }
            }
        }
    }
        
}
