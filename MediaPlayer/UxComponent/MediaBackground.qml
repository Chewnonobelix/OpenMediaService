import QtQuick 2.15
import QtQuick.Controls.Material 2.12

Rectangle {
	id: root

	color: "#404040"

	Rectangle {
		gradient: Gradient {
			GradientStop {
				color: "blue"
				position: 0.0
			}
			GradientStop {
				color: "green"
				position: 0.5
			}
			GradientStop {
				color: "red"
				position: 1.0
			}
		}
			anchors {
			left: root.left
			top: root.top
		}

		width: parent.width + 1
		height: parent.height + 1
		z: -1
	}
}
