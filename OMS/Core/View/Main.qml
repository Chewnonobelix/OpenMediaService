import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0

ApplicationWindow {
    id: root

    Component.onCompleted: {
        show()
    }

    width: 600
    height: 400

    Shortcut {
        sequence: "Ctrl+Q"
        onActivated: root.close()
    }

    menuBar: MediaMenuBar {
        onQuit: root.close()
    }


    SplittingView {
        anchors.fill: parent
    }
}
