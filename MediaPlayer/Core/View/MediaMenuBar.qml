import QtQuick 2.15
import QtQuick.Controls 2.15

import MediaPlayer.Components 1.0

MenuBar {
    id: root

    signal quit()

    Menu {
        title: "File"

        MenuItem {
            text: "Settings"
            onClicked: _settings.display()
        }

        MenuItem {
            text: "Quit"

            onClicked: root.quit()
        }
    }
}
