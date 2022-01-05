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
        Column {
            Row  {
                MediaLabel {
                    text: qsTr("Reading count")
                    height: root.height * 0.05
                    width: root.width * 0.5
                }

                MediaLabel {
                    text: model.count
                    height: root.height * 0.05
                    width: root.width * 0.40
                }
                MediaButton {
                    text: qsTr("Reset")
                    height: root.height * 0.05
                    width: root.width * 0.10

                    onClicked: {
                        model.reset()
                    }
                }
            }
            Row  {
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
            }
            Row  {
                MediaLabel {
                    text: qsTr("Last readed")
                    height: root.height * 0.05
                    width: root.width * 0.5
                }

                MediaLabel {
                    text: Qt.formatDateTime(model.lastFinish, "dd-MM-yyyy hh:mm:ss")
                    height: root.height * 0.05
                    width: root.width * 0.5
                }
            }
            Row  {
                MediaLabel {
                    text: qsTr("Added")
                    width: root.width * 0.5
                    height: root.height * 0.05
                }

                MediaLabel {
                    text: Qt.formatDate(model.added, "dd-MM-yyyy")
                    height: root.height * 0.05
                    width: root.width * 0.5
                }
            }
            Row  {
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
            }
            Row  {
                MediaLabel {
                    text: qsTr("Paths")
                    height: root.height * 0.05
                    width: root.width * 0.5
                }

                ListView {
                    model: root.model.paths
                    height: root.height * 0.20
                    width: root.width * 0.5
                    clip: true

                    delegate: MediaLabel {
                        text: modelData
                        height: root.height * 0.05
                        width: root.width * 0.5
                    }
                }
            }
            Row  {
                MediaLabel {
                    text: qsTr("Tags")
                    height: root.height * 0.05
                    width: root.width * 0.5
                }

                ListView {
                    model: root.model.tags
                    height: root.height * 0.20
                    width: root.width * 0.5
                    clip: true

                    delegate: MediaLabel {
                        text: modelData
                        height: root.height * 0.05
                        width: root.width * 0.5
                    }
                }
            }

        }
    }
}
