pragma Singleton
import QtQuick 2.15

QtObject {
    property Gradient selected: Gradient {
        GradientStop {
            color: "black"
            position: 0.0
        }

        GradientStop {
            color: "darkblue"
            position: 0.40
        }

        GradientStop {
            color: "aqua"
            position: 0.5
        }

        GradientStop {
            color: "darkblue"
            position: 0.60
        }

        GradientStop {
            color: "black"
            position: 1.0
        }
    }

    property Gradient unselected1: Gradient {
        GradientStop {
            color: "grey"
        }
    }

    property Gradient unselected2: Gradient {
        GradientStop {
            color: Qt.lighter("grey", 0.5)
        }
    }
}
