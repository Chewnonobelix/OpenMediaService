import QtQuick 2.15
import QtQuick.Controls 2.15

import MediaPlayer.Components 1.0

Item {
    id: root
    HorizontalHeaderView {
        id: header
        height: root.height * .10
        width: root.width
        syncView: table
    }
    TableView {
        id: table

        anchors {
            top: header.bottom
            left: root.left
            right: root.right
            bottom: root.bottom
        }

        model: _imageListModel


        delegate: MediaLabel {
            text: display
        }
    }
}
