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
        }
        
        ListView {
            id: playlistView
            objectName: "playlistView"
            Layout.row: 1
            Layout.column: 1             
            Layout.preferredWidth: parent.width * .2            
            Layout.fillHeight: true
            clip: true
        }
        
        GridView {
            id: mediaView
            objectName: "mediaView"
            Layout.row: 1
            Layout.column: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
        }
    }
        
}
