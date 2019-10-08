import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4 as C
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13


ApplicationWindow {
    visible: true
    width: 640
    height: 480
        
    menuBar: MenuBar {
        id: menuBar
        
        Menu {
            id: file
            title: qsTr("File")
        }
        
    }
    
    
    Rectangle {
//        anchors.top: menuBar.bottom
//        anchors.bottom: parent.bottom
//        anchors.right: parent.right
//        anchors.left: parent.left
                        anchors.fill: parent
        
                ListModel {
                    id: tabModel
                    ListElement {
                        name: qsTr("Library")
                    }
                    ListElement {
                        name: qsTr("+")
                    }
                }
        
        TabBar {
            id: bar
            width: parent.width
            Repeater
            {
                id: rep
                model: tabModel
                TabButton {
                    text: modelData
                    onClicked: {
                        if(index === rep.model.count - 1) {
                            var i = rep.model.count - 2                           
                            rep.model.insert(rep.model.count - 1, { "name": "Tab " + i})
                            bar.currentIndex = i+1
                        }
                    }
                }
            }        
        }
        StackLayout {
            id: mainTab
            anchors.top: bar.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            currentIndex: bar.currentIndex
            Rectangle {
//                anchors.fill:parent
                //                title: qsTr("Library")
                ListView {
                    id: libraryView
                    objectName: "libraryView"
                    //                    visible: showLibrary.on

                    model: []
                    onModelChanged: { 
                        console.log(model/*, model[100], model[100].count, model[100].path()*/)
//                        forceLayout()
                    }
                    anchors.fill: parent
                    clip: true
                    delegate: Rectangle {
                        height: 40
                        width: libraryView.width
                           
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                console.log(modelData, modelData.paths)
                                modelData.pp()
                            }
                        }

                        Text {
                            text: modelData.count
                        }
                    }
                }
                
            }
        }
        
    }
}
