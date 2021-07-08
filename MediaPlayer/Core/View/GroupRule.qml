import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.qmlmodels

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0


Item {
    id: root
    property var groups: null
    TableView {
        id: list
        anchors.fill: parent
        clip: true
        model: _smartModel


        columnWidthProvider: function(c) {
            return root.width / 10
        }

        delegate: DelegateChooser {
            role: "type"
            DelegateChoice {
                roleValue: "rule"
                SmartRule {
                }
            }

            DelegateChoice {
                roleValue: "group"
                RowLayout {
                    MediaCombobox {
                        model: ["Or", "And"]
                    }
                    MediaButton {
                        text: "+"

                        onClicked: list.model.add(row, false)
                    }
                    MediaButton {
                        text: "_"
                        onClicked: list.model.add(row, true)
                    }
                    MediaButton {
                        text: "-"
                    }
                }
            }
        }
    }
}
