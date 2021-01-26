import QtQuick 2.15
import QtQuick.Controls 2.15

ItemDelegate {
	id: root

	function isCurrentIndex() {
		return ListView.view.currentIndex === index
	}

	property bool lock: false

	onClicked: {
		ListView.view.currentIndex = isCurrentIndex() ? -1 : index
	}

	onDoubleClicked: {
		if(!lock) {
			console.log("Edit")
		}
	}




	background: Rectangle {
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

		property Gradient unselected: Gradient {
			GradientStop {
				color: "transparent"
			}
		}

		gradient: isCurrentIndex() ? selected : unselected
	}
}
