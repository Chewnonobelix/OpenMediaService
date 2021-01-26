import QtQuick 2.15
import QtQuick.Controls 2.15

ItemDelegate {
	function isCurrentIndex() {
		return ListView.view.currentIndex === index
	}

	onClicked: {
		ListView.view.currentIndex = isCurrentIndex() ? -1 : index
	}

	background: Rectangle {
		color: isCurrentIndex() ? "lightblue" : "transparent"
	}
}
