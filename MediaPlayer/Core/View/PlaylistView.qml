import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0

MediaWindow {
    id: root
    flags: Qt.Dialog

    Component.onCompleted: {
        visible = true
    }

    title: "Playlist " + (_playlist ? _playlist.name : "")

    width: 400
    height: 600

    GridLayout {
        anchors.fill: parent
        columns:  2

        MediaLabel {
            text: "Playlist name"

            Layout.preferredWidth: root.width * .20
            Layout.preferredHeight: root.height * .10
        }

        MediaTextEdit {
            text: _playlist ? _playlist.name : ""

            onEditingFinished: _playlist.name = text

            Layout.preferredHeight: root.height * .10
            Layout.fillWidth: true
        }

        GroupRule {

            visible: _smart
            Layout.columnSpan: 2
            Layout.fillHeight: true
            Layout.fillWidth: true

            groups: _playlist.rule
        }
    }
}
