import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer.Components 1.0

Window {
    ColumnLayout {
        anchors.fill: parent
        GroupBox {
            title: "Language"
        }

        GroupBox {
            title: "DB"
        }

        GroupBox {
            title: "Plugins"
        }

        GroupBox {
            title: "Sync"
        }

        GroupBox {
            title: "Stream"
        }
    }
}
