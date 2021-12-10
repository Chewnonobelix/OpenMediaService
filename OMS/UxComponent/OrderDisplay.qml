import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer.Model 1.0

Item {
    id: root
    property bool isExpand: false
    property OrderDisplayModel model

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: list
            model: root.model
            Layout.fillHeight: true
            delegate: ItemDelegate {
                visible:  isExpand || index < 5
                text: path
            }
        }

        Label {
            text:  isExpand ? "^ reduce ^" : "v expand v"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    isExpand = !isExpand
                }
            }
        }
    }
}
