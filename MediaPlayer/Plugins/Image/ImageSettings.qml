import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer.Components 1.0

Item {


    GridLayout {
        anchors.fill: parent
        columns: 3
        rows: 2
        MediaCombobox {
            id: aspectRatio

            model: ["Fill", "Fit", "Custom"]

            onCurrentIndexChanged: {
                _settings.setValue("Image/Ratio", currentText)
            }
        }

        SpinBox {
            id: imageWidth
            enabled: aspectRatio.currentIndex === 2

            from: 1
            to: 1920

            editable: true
            onValueChanged: _settings.setValue("Image/Width", value)
        }
        SpinBox {
            id: imageHeight
            enabled: aspectRatio.currentIndex === 2

            from: 1
            to: 1080

            editable: true
            onValueChanged: _settings.setValue("Image/Height", value)
        }

        ListView {
            id: columnOrder
        }
    }
}
