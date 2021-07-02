import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.qmlmodels

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0


Item {
    id: root

    GroupBox {
        anchors.fill: parent

        label: MediaCombobox {
            model: ["And", "Or"]
        }

        ListView {
            anchors.fill: parent
            header: MediaLabel {
                text: "Smart rules"
            }

            delegate: DelegateChooser {
                role: "type"
                DelegateChoice {
                    roleValue: "group"
                    Node {

                    }
                }
                DelegateChoice {
                    roleValue: "rule"
                    SmartRule {

                    }
                }
            }
        }
    }
}
