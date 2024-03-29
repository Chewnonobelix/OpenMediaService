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
            Component.onCompleted: {
                if(_settings.value("Image/Ratio") === "Fit") {
                    currentIndex = 0
                }
                else if(_settings.value("Image/Ratio") === "Fill") {
                    currentIndex = 1
                }
                else {
                    currentIndex = 2
                }
            }
            id: aspectRatio

            model: [qsTr("Fit"), qsTr("Fill"), qsTr("Custom")]

            onActivated: {
                _settings.setValue("Image/Ratio", currentText)
            }
        }

        SpinBox {
            Component.onCompleted: if(_settings.value("Image/Width")) value = _settings.value("Image/Width")
            id: imageWidth
            enabled: aspectRatio.currentIndex === 2

            from: 1
            to: 1920

            value: to
            editable: true
            onValueModified: _settings.setValue("Image/Width", value)
        }
        SpinBox {
            Component.onCompleted: if(_settings.value("Image/Height")) value = _settings.value("Image/Height")
            id: imageHeight
            enabled: aspectRatio.currentIndex === 2

            from: 1
            to: 1080
            value: to
            editable: true
            onValueModified: _settings.setValue("Image/Height", value)
        }

        MediaLabel {

            text: qsTr("Interval")
        }

        SpinBox {
            id: interval
            Component.onCompleted: value = _settings.value("Image/Interval") ? _settings.value("Image/Interval") : 2

            onValueModified: _settings.setValue("Image/Interval", value)
        }
    }
}
