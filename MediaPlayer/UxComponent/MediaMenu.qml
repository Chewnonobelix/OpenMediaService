import QtQuick 2.15
import QtQuick.Controls 2.15

Menu {
    id: root

    signal remove()

    MenuItem {
        text: "Remove media"

        onClicked: root.remove()
    }
}
