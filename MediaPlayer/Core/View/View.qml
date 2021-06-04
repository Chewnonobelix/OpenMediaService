import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0


Item {
    id: root

    property int index: -1
    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: true
        onClicked: function(mouse) {
            mouse.accepted = false
            //            root.clicked(index)
        }
    }

    signal tabSelection (int indexLib, int plyalistLib)

    SplitView.fillHeight: SplitView.view.count == 1 || SplitView.view.orientation === Qt.Horizontal
    SplitView.fillWidth: SplitView.view.count == 1 || SplitView.view.orientation === Qt.Vertical
    SplitView.onFillWidthChanged: {
        if(!SplitView.fillWidth)
            SplitView.preferredWidth = SplitView.view.width / SplitView.view.count
    }

    SplitView.onFillHeightChanged: {
        if(!SplitView.fillHeight)
            SplitView.preferredHeight = SplitView.view.height / SplitView.view.count
    }

    function setLibraryIndex(index) {
        //        viewRep.itemAt(viewBar.currentIndex).setIndex(index)
    }

    ColumnLayout {
        anchors.fill: parent

        TabBar {
            id: viewBar

            Layout.fillWidth: true
            Layout.preferredHeight: root.height * 0.10

            Component.onCompleted: {
                currentIndex = 0
            }

            Repeater {
                id: tabRepeater
                model: 0

                MediaTabButton {
                    text: qsTr("Tab ") + modelData

                    onClicked: {
                        _tabWrapper.setCurrentTab(view.itemAt(modelData).id)
                    }
                }
            }

            MediaTabButton {
                text: "+"

                Component.onCompleted: onClicked()
                onClicked:  {
                    tabRepeater.model = viewBar.currentIndex + 1
                    viewBar.currentIndex = viewBar.currentIndex - 1
                    viewRep.model.addTab()
                }
            }
        }

        StackLayout {
            id: view
            currentIndex: viewBar.currentIndex
            Layout.fillWidth: true
            Layout.fillHeight: true

            clip: true


            onCurrentIndexChanged: {
            }




            Repeater {
                id: viewRep
                Component.onCompleted:  {
                    var id = _tabWrapper.create()
                    model = _tabWrapper.get(id);
                }

                Loader {
                    id: playerLoader
                    active: true

                    sourceComponent: model.player

                    property string id: model.id

                    property Playlist pl: model.playlist

                    onPlChanged: console.log(pl)
                    visible: true

                    property Media media
                }
            }
        }
    }
}
