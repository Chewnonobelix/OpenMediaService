pragma Singleton
import QtQuick 2.15

QtObject {
    property int play: 0
    property int stop: 1

    function next(value) {
        return value === 0 ? 1 : 0
    }
}
