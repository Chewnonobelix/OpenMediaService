import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0


MediaWindow {
    Component.onCompleted: show()
    Component.onDestruction: {
        for(var i = 0; i < split.idList().length; i++) {
            _tabWrapper.removeManager(split.idList()[i])
        }
    }

    onClosing: _liveQmlEngine.removeWindow(this)
    SplittingView {
        id: split
        anchors.fill: parent
    }
}
