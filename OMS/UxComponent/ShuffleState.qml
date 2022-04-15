pragma Singleton
import QtQuick 2.15

QtObject {
    property int real: 0
    property int random: 1

    function next(value) {
        return value === 0 ? 1 : 0
    }
}
