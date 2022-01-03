import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Menu {
    id: root
    property var model
    signal loadBookmark(string mark)
    signal addBookmark()
    signal removeBookmark(string bookmark)

    title: qsTr("Bookmark")

    Action {
        id: add
        text: qsTr("Add bookmark")

        onTriggered: root.addBookmark()
    }

    Instantiator {
        model:  root.model
        id: instant
        delegate: Menu {
            title: modelData
            Action {
                text: qsTr("Load")
                onTriggered: root.loadBookmark(modelData)
            }

            Action {
                text: qsTr("Remove")
                onTriggered: root.removeBookmark(modelData)
            }
        }

        onObjectAdded: function(index, obj) {
            root.addMenu(obj)
        }

        onObjectRemoved: function(index, obj) {
            root.removeMenu(obj)
        }
    }
}
