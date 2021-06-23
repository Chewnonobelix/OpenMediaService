import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0

MediaWindow {
    id: root
    flags: Qt.Dialog

    Component.onCompleted: visible = true

    title: "Playlist " + (_playlist ? _playlist.name : "")


    GridLayout {
        anchors.fill: parent

        MediaLabel {
            text: "Playlist name"
        }

        MediaTextEdit {
            text: _playlist ? _playlist.name : ""

            onEditingFinished: _playlist.name = text
        }
    }
}
