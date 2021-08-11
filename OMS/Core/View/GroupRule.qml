import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.qmlmodels

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0


Item {
    id: root
    TableView {
        id: list
        anchors.fill: parent
        clip: true
        model: _smartModel


        columnWidthProvider: function(c) {
            return root.width / 10
        }

        rowHeightProvider: function(c) { return root.height * .2}
        delegate: DelegateChooser {
            role: "type"
            DelegateChoice {
                roleValue: "rule"
                RowLayout {

                    MediaButton {
                        text: "-"

                        onClicked: console.log("Remove rule", _smartModel.remove(id), id)
                    }
                    SmartRule {

                    }
                }
            }

            DelegateChoice {
                roleValue: "group"
                RowLayout {
                    MediaCombobox {
                        Component.onCompleted:  {
                            currentIndex = find(op) > -1 ? find(op) : 0
                        }

                        model: [qsTr("Or"), qsTr("And")]

                        onActivated: {
                            op = currentText
                        }
                    }
                    MediaButton {
                        text: "+"

                        onClicked: list.model.add(row, false)
                    }
                    MediaButton {
                        text: "_"
                        onClicked: list.model.add(row, true)
                    }
                    MediaButton {
                        text: "-"
                        onClicked: console.log("Remove group", _smartModel.remove(id))
                    }
                }
            }
        }
    }
}
