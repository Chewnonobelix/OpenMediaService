import QtQuick 2.15
import QtQuick.Controls 2.15

import MediaPlayer.Model 1.0

Button {
    id: root
    property OrderDisplayModel model
    property int popupWidth: 0
    property int popupHeight: 0
    property bool popAnchorsLeft: false

    enum AnchorType {
        Left,
        Right,
        Top,
        Bottom
    }

    property int positionning: ButtonOrder.AnchorType.Right
    icon {
        height: root.height
        width: root.width
        source: "qrc:/icons/playlist.png"
    }


    Menu {
        id: pop

        Bookmark {
            model: ["B1", "B2", "B3"]
        }
    }

//    Popup {
//        id: pop

//        width: root.popupWidth
//        height: (display.isExpand ? 2 : 1) * root.popupHeight

//        x: positionning === ButtonOrder.AnchorType.Right ? root.width : positionning === ButtonOrder.AnchorType.Left ? -width : -width/2 + root.width / 2
//        y: positionning === ButtonOrder.AnchorType.Top ? -height : positionning === ButtonOrder.AnchorType.Bottom ? root.height : 0

//        Bookmark {
//            model: ["B1", "B2", "B3"]
//        }

////        OrderDisplay {
////            id: display
////            anchors.fill: parent
////            model: root.model
////        }
//    }

    onClicked: pop.open()
}
