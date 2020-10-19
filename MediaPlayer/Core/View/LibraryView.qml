import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

import MediaPlayer 1.0

Window {
    id: root
    flags: Qt.Dialog

    required property Library currentLibrary

    title: currentLibrary.name

    Connections {
        target: _libraries

        function onCurrentLibraryChanged() {
            currentLibrary = _libraries.currentLibrary
        }
    }

    GridLayout {
        anchors.fill: parent

        Rectangle {
            Column {
                anchors.fill: parent

                Label {
                    text: "Role" + ": " + currentLibrary.role
                }
                Label {
                    text: "Last update" + ": " + currentLibrary.lastUpdate
                }
                Label {
                    text: "Media count" + ": " + currentLibrary.medias().size()
                }
                Label {
                    text: "Playlist count" + ": "
                }
            }
        }

        ListView {
            model: currentLibrary.sourceDir()
        }

    }
}
