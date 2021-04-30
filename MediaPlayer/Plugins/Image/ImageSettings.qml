import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer.Components 1.0

Item {

    Row {
        MediaCombobox {
            id: aspectRatio

            model: ["Fill", "Fit", "Custom"]
        }

        SpinBox {
            id: imageWidth
            enabled: aspectRatio.currentIndex === 2
        }
        SpinBox {
            id: imageHeight
            enabled: aspectRatio.currentIndex === 2
        }
    }

    ListView {
        id: columnOrder
    }
}
