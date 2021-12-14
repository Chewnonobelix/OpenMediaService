import QtQuick 2.15
import QtQuick.Controls 2.15

import MediaPlayer.Model 1.0

Button {
    id: root
    property OrderDisplayModel model
    property int popupWidth: 0
    property int popupHeight: 0
    property bool popAnchorsLeft: false

    icon {
        height: root.height
        width: root.width
        source: "qrc:/icons/playlist.png"
    }

    Popup {
        id: pop

        width: root.popupWidth
        height: (display.isExpand ? 2 : 1) * root.popupHeight

        x: popAnchorsLeft ? -width : root.width

        OrderDisplay {
            id: display
            anchors.fill: parent
            model: root.model
        }
    }

    onClicked: pop.open()
}
