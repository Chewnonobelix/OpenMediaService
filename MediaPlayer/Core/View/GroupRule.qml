import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.qmlmodels

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0


Item {
    id: root
    property SmartGroup groups
    GroupBox {
        anchors.fill: parent

        label: MediaCombobox {
            model: ["And", "Or"]
        }

        ListView {
            id: list
            anchors.fill: parent
            model: SmartModel {
                group: root.groups
            }

            header: MediaLabel {
                text: "Smart rules"
            }

            delegate: Loader {
                source: type === "group" ? "GroupRule.qml" : "SmartRule.qml"

                    }
            }
        }
    }
}
