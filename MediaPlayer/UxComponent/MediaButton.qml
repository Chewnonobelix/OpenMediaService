import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
	id: root

	background: MediaBackground {}

	contentItem: Label {
		text: root.text
		color: root.down || root.hovered ? "black" : "white"
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
		opacity: enabled ? 1.0 : 0.3
	}
}
