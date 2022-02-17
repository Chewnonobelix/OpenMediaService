import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0


MediaWindow {
    Component.onCompleted: show()
    SplittingView {
        id: split
        anchors.fill: parent
    }
}
