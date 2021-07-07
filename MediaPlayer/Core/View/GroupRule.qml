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
        model: SmartModel {
            group: root.groups
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
                MediaCombobox {
                    model: ["Or", "And"]
                }
            }
        }
    }
}
