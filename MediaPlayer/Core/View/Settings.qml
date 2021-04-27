import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer.Components 1.0

MediaWindow {
    id: root
    flags: Qt.Dialog
    Component.onCompleted: {
        visible = true
    }

    width: 400
    height: 600
    ColumnLayout {
        anchors.fill: parent
        GroupBox {
            title: "Language"
        }

        GroupBox {
            title: "DB"
        }

        GroupBox {
            title: "Plugins"

            ColumnLayout {
                anchors.fill: parent

                Repeater {
                    model: _plugins

                    MediaCheckbox {
                        text: name
                        checked: enable

                        onCheckedChanged: enable = checked
                    }
                }
            }
        }

        GroupBox {
            title: "Sync"
        }

        GroupBox {
            title: "Stream"
        }
    }
}
