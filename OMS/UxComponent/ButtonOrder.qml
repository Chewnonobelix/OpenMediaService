import QtQuick 2.15
import QtQuick.Controls 2.15

import MediaPlayer.Model 1.0

Button {
    id: root
    property OrderDisplayModel model
    property int popupWidth: 0
    property int popupHeight: 0

    Popup {
        id: pop

        width: root.popupWidth
        height: (display.isExpand ? 2 : 1) * root.popupHeight

        OrderDisplay {
            id: display
            anchors.fill: parent
            model: root.model
        }
    }

    onClicked: pop.open()
}
