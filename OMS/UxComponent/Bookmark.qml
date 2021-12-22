import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

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

    Instantiator {
        model:  root.model
        id: instant
        delegate: Menu {
            Component.onCompleted: console.log("prout", modelData, instant.count, root.count)
            title: modelData
            MenuItem {
                text: qsTr("Remove")
                onClicked: console.log("remove", modelData)
            }
        }

        onObjectAdded: function(index, obj) {
            root.addMenu(obj)
        }
    }
}
