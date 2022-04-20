pragma Singleton
import QtQuick 2.15

QtObject {
    property int play: 0
    property int stop: 1
    property int pause: 2

    function next(value) {
        return value === 2 ? 0 : 2
    }
}
