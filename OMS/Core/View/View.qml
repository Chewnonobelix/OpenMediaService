import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0


Item {
    id: root

    property int index: -1
    property string idTab: viewRep.model ? viewRep.model.id(): ""

    signal clicked(int index)
    signal newWindow()
    signal newView()
    signal remove(string tab)

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        propagateComposedEvents: true
        onClicked: function(mouse) {
            _tabWrapper.setCurrentTab(viewRep.itemAt(viewBar.currentIndex).id)
            mouse.accepted = false
            root.clicked(root.index)
        }
    }

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
                    text: qsTr("Tab") + " " + modelData

                    onClicked: {
                        _tabWrapper.setCurrentTab(view.itemAt(modelData).id)
                    }

                    ToolButton {
                        text: "x"

                        anchors {
                            right: parent.right
                            top: parent.top
                        }

                        onClicked: {
                            var ret = viewRep.model.removeTab(view.itemAt(modelData).id)
                            console.log("Remove tab", ret)

                            if(ret) {
                                viewBar.currentIndex = 0
                                tabRepeater.model = tabRepeater.model - 1
                            }
                        }
                    }
                }
            }

            MediaTabButton {
                text: "+"

                onClicked: {
                    menuWindow.x = mapToGlobal(0,0).x
                    menuWindow.open()
                }
            }

            Menu {
                id: menuWindow
                Action {
                    Component.onCompleted: triggered()
                    text: qsTr("Open in new tab")
                    onTriggered:  {
                        tabRepeater.model = viewBar.currentIndex + 1
                        viewBar.currentIndex = viewBar.currentIndex - 1
                        viewRep.model.addTab()
                    }
                }
                Action {
                    text: qsTr("Open in new view")
                    onTriggered: root.newView()
                }
                Action {
                    text: qsTr("Open in new window")
                    onTriggered: root.newWindow()
                }
                Action {
                    text: qsTr("Remove current view")
                    onTriggered: root.remove(idTab)
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

                Item {
                    id: pRoot
                    property string id: model.id
                    property Item rPlayer: model.player
                    Item {

                    }

                    onRPlayerChanged: {
                        pRoot.children[0] = rPlayer
                        rPlayer.anchors.fill = pRoot
                    }
                }
            }
        }
    }
}
