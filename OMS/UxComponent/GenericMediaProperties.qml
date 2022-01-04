import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0

Item {
    id: root

    property Media model

    ScrollView {
        anchors.fill: parent
        GridLayout {
            column: 2

            MediaLabel {
                text: qsTr("Reading count")
                height: root.height * 0.05
                width: root.width * 0.5
            }

            MediaLabel {
                text: model.count
                height: root.height * 0.05
                width: root.width * 0.5
            }

            MediaLabel {
                text: qsTr("Current reading")
                height: root.height * 0.05
                width: root.width * 0.5
            }

            MediaLabel {
                text: model.currentRead
                height: root.height * 0.05
                width: root.width * 0.5
            }

            MediaLabel {
                text: qsTr("Last readed")
                height: root.height * 0.05
                width: root.width * 0.5
            }

            MediaLabel {
                text: model.lastFinish
                height: root.height * 0.05
                width: root.width * 0.5
            }

            MediaLabel {
                text: qsTr("Added")
                width: root.width * 0.5
                height: root.height * 0.05
            }

            MediaLabel {
                text: model.added
                height: root.height * 0.05
                width: root.width * 0.5
            }

            MediaLabel {
                text: qsTr("Rate")
                height: root.height * 0.05
                width: root.width * 0.5
            }

            MediaLabel {
                text: model.rating
                height: root.height * 0.05
                width: root.width * 0.5
            }

            MediaLabel {
                text: qsTr("Paths")
                height: root.height * 0.05
                width: root.width * 0.5
            }

            ListView {
                model: model.paths
                height: root.height * 0.20
                width: root.width * 0.5

                delegate: MediaLabel {
                    text: modelData
                    height: root.height * 0.05
                    width: root.width * 0.5
                }
            }

            MediaLabel {
                text: qsTr("Tags")
                height: root.height * 0.05
                width: root.width * 0.5
            }

            ListView {
                model: model.tags
                height: root.height * 0.20

                delegate: MediaLabel {
                    text: modelData
                    height: root.height * 0.05
                    width: root.width * 0.5
                }
            }
        }
    }
}
