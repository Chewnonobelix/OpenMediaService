import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0


Menu {
    id: root
    title: qsTr("Tag")

    signal removeTag(string uid)
    signal addTag(string uid)

    property TagModel model
    property var tagList

    function indexOf(l, v) {
        var ret = -1
        if(l && v) {
            for(var i = 0; i < l.length; i++) {
                if(l[i] == v) {
                    ret = i
                }
            }
        }

        return ret
    }

    MenuItem {
        text: qsTr("New tag")

        onClicked: popTag.open()

        Popup {
            id: popTag

            onOpened: {
                addTag.clear()
            }

            onClosed: {
                if(addTag.text !== "") {
                    var uid = root.model.addTag(addTag.text)
                    if(uid !== "")
                       root.addTag(uid)
                }
            }

            GridLayout {
                anchors.fill: parent
                columns: 2
                rows: 2
                MediaTextEdit {
                    id: addTag
                    Layout.columnSpan: 2
                }

                MediaButton {
                    text: qsTr("Add")
                    onClicked: popTag.close()
                }

                MediaButton {
                    text: qsTr("Cancel")

                    onClicked: {
                        addTag.clear()
                        popTag.close()
                    }
                }
            }
        }
    }

    Repeater {
        id: tagRepeater
        model: root.model

        MenuItem {
            text: tag
            checkable: true
            checked: root.indexOf(tagList, uid) !== -1

            onClicked: {
                if(checked)
                    root.addTag(uid)
                else
                    root.removeTag(uid)
            }

            Menu {
                MenuItem {
                    text: qsTr("Remove")
                }

                MenuItem {
                    text: qsTr("Edit")
                }
            }
        }
    }
}
