pragma Singleton
import QtQuick 2.15

QtObject {
    property int realOrder: 0
    property int random: 1

    function next(value) {
        return value === realOrder ? random : realOrder
    }
}
