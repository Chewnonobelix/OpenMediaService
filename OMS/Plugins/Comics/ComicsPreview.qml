import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Item {
    id: root
    Rectangle {
        anchors.fill: parent
        color: "transparent"
    }

    ScrollView {
        anchors.fill: parent

        Row {
            topPadding: root.height * 0.05
            spacing: root.width * 0.02
            Repeater {
                model: _player

                Image {
                    height: root.height * 0.90
                    width: root.width * 0.05

                    source: "file:///"+page
                }
            }
        }
    }
}
