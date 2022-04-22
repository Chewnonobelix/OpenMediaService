import QtQuick 2.0

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MediaPlayer.Components 1.0

Item {
    ColumnLayout {
        anchors.fill: parent
        MediaCombobox {
            id: typeCombo
            model: ["Column"]

            onCurrentIndexChanged: stack.currentIndex = currentIndex
        }

        StackLayout {
            id: stack
            currentIndex: typeCombo.currentIndex
            PlaylistList {
                model: _playlistListModel
            }
        }
    }
}
