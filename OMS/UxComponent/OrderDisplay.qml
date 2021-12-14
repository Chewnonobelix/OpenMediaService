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
            Layout.fillWidth: true
            delegate: ItemDelegate {
                visible:  isExpand || index < 5
                text: path
                width: list.width
                height: isExpand ? list.height * 0.1 : list.height * 0.2
            }
        }

        Label {
            text:  isExpand ? "^ reduce ^" : "v expand v"
            Layout.preferredHeight: root.height * 0.05
            Layout.fillWidth: true

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    isExpand = !isExpand
                }
            }
        }
    }
}
