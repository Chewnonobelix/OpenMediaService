import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    property int index: -1

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton

        onWheel: function(wheel) {
            if(wheel.angleDelta.y > 0 && layout.currentIndex > 0) {
                layout.currentIndex --
            }
            else if(wheel.angleDelta.y < 0 && layout.currentIndex < rep.count - 1) {
                layout.currentIndex ++
            }
        }
    }

    StackLayout{
        id: layout
        anchors.fill: parent
        onCountChanged: currentIndex = _player.currentPage
        onCurrentIndexChanged: _player.currentPage = currentIndex
        Repeater {
            id: rep
            model: _player
            Image {
                id: display
                source: "file:///"+page
            }
        }
    }
}
