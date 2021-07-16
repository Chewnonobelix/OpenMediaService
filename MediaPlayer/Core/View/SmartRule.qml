import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0

Item {
    id: root

    RowLayout {
        anchors.fill: parent

        MediaCombobox {
            id: fieldCombo

            currentIndex: find(field)
            model: fields

            onActivated: field = currentText
        }

        MediaCombobox {
            id: opCombo
            currentIndex: find(op)

            model: _smartModel.ops(fieldCombo.currentText)
            onActivated: op = currentText
        }

        MediaTextEdit {
            id: valueEdit

            text: value ? value : ""
            onEditingFinished: value = text
        }
    }
}
