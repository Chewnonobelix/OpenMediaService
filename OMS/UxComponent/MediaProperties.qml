import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import Qt.labs.platform 1.1

import MediaPlayer 1.0
import MediaPlayer.Components 1.0

MediaWindow {
    id: root
    flags: Qt.Dialog

    Component.onCompleted: show()
    height: 400
    width: 300

    TabBar {
        id: bar
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        height: parent.height * 0.10

        onCurrentIndexChanged: layout.currentIndex = currentIndex

        TabButton {
            text: qsTr("General")
            height: bar.height
        }

        Repeater {
            model: _pagesList

            TabButton {
                text: modelData
                height: bar.height
            }
        }
    }

    StackLayout {
        id: layout
        anchors {
            top: bar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom

            topMargin: root.height * 0.03
        }

        GenericMediaProperties {
            model: _media
        }

        Repeater {
            model: _pages

            Item {
                ColumnLayout {
                    anchors.fill: parent
                    Item{
                    }

                    Component.onCompleted:  {
                        children[0] = modelData
                    }
                }
            }
        }
    }

}
