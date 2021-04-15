import QtQuick 2.15
import QtQuick.Controls 2.15

import MediaPlayer.Components 1.0

TableView {
    id: root

    model: _imageListModel


    delegate: MediaLabel {
        text: display
    }
}
