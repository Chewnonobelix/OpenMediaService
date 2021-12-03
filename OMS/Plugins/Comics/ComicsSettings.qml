import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MediaPlayer.Components 1.0

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent

//        MediaCheckbox {
//            text: qsTr("Left to right")
//            checked: _settings.value("Comics/rightToLeft")
//            onClicked: _settings.setValue("Comics/rightToLeft", checked)
//        }

        MediaCheckbox {
            text: qsTr("Split double page")
            checked: _settings.value("Comics/split")
            onClicked: _settings.setValue("Comics/split", checked)
        }

        Item {
            id: spacer
            Layout.fillHeight: true
        }
    }
}
