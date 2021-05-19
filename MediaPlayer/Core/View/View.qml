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
            root.clicked(index)
        }
    }

    signal clicked (int index)

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
        viewRep.itemAt(viewBar.currentIndex).setIndex(index)
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

                    onClicked: repModel.setCurrentTab(view.itemAt(modelData).idTab)
                }
            }

            MediaTabButton {
                text: "+"

                Component.onCompleted: onClicked()
                onClicked:  {
                    tabRepeater.model = viewBar.currentIndex + 1
                    viewBar.currentIndex = viewBar.currentIndex - 1
                    repModel.addTab()
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
                model: TabManager {
                    id: repModel
                }

                Loader {
                    id: playerLoader
                    active: true

                    Component.onCompleted: {
                        repModel.setCurrentTab(idTab)
                    }

                    visible: true
                    property string idTab: id

                    function setIndex(index) {
                        model.library = index
                        sourceComponent = _librariesModel.controller(index).playerComponent
                        connect.target = _librariesModel.controller(index)
                    }

                    property Media media
                    Connections {
                        id: connect
                        target: model

                        ignoreUnknownSignals: true

                        function onPlay(media) {
                            playerLoader.media = media
                        }
                    }
                }
            }
        }
    }
}
