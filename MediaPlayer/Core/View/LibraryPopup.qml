import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0

Popup {
	id: root

	onOpened: libraryName.clear()
	GridLayout {
		anchors.fill: parent
		rows: 2

		MediaTextEdit {
			id: libraryName
			width: addLibraryPop.width* 0.40

			validator: RegularExpressionValidator {
				regularExpression : /.+/
			}
		}

		MediaCombobox {
			id: libraryType
            Component.onCompleted: {
                var list = _plugins.pluginsName()
                for(var it in list) {
                    var role = _plugins.pluginRole(list[it])
                    typeModel.append({"name": list[it], "role": role})
                }
                currentIndex = 0
            }


            model: ListModel {
                id: typeModel
            }

            editable: false
			textRole: "name"
			valueRole: "role"

            delegate: ItemDelegate {
                text: name
                enabled: _plugins.pluginEnable(name)
                visible: _plugins.pluginEnable(name)
                width: libraryType.width

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.NoButton
                    cursorShape: enabled ? Qt.PointingHandCursor : Qt.ArrowCursor
                }
             }
		}

		MediaButton {
			Layout.preferredHeight: addLibraryPop.height * .5
			Layout.preferredWidth: addLibraryPop.width * .19
			enabled: libraryName.acceptableInput
			text: "Add"
			onClicked: {
				_db.createLibrary(libraryName.text, libraryType.currentValue)
				addLibraryPop.close()
			}
		}
		MediaButton {
			Layout.preferredHeight: addLibraryPop.height * .5
			Layout.preferredWidth: addLibraryPop.width * .19
			text: "Close"
			onClicked: {
				addLibraryPop.close()
			}
		}
	}
}
