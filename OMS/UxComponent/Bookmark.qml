import QtQuick 2.15
import QtQuick.Controls 2.15

Menu {
    id: root
    property var model
    signal loadBookmark(string mark)
    signal addBookmark()

    title: qsTr("Bookmark")

    MenuItem {
        id: add
        text: qsTr("Add bookmark")

        onClicked: root.addBookmark()
    }

    Repeater {
        model:  root.model

        MenuItem {
            text: "modelData"

            MenuItem {
                text: qsTr("Remove")
                onClicked: console.log("remove", modelData)
            }

            onClicked: console.log("load", modelData)
        }
    }
}
