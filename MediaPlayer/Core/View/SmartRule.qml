import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0

Item {
    id: root

    property var fields

    RowLayout {
        anchors.fill: parent

        MediaCombobox {
            id: field

            model: fields
        }

        MediaCombobox {
            id: op
        }

        MediaTextEdit {
            id: value
        }
    }
}
