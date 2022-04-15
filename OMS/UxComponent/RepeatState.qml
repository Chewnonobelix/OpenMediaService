pragma Singleton
import QtQuick 2.0

QtObject {
    id: root

    property int no: 0
    property int all: 1
    property int one: 2

    function next (value) {
        return (value + 1) % 3
    }
}
