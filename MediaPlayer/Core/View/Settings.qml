import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer.Components 1.0

MediaWindow {
    id: root
    flags: Qt.Dialog
    Component.onCompleted: {
        visible = true
    }

    width: 400
    height: 600

    Column {
        id: tabColumn

        property int currentIndex: 0

        anchors {
            top: root.top
            left: root.left
        }

        width: root.width * 0.20
        height: root.height


        MediaButton {
            id: generalTab
            text: "General"
            onClicked: {
                tabColumn.currentIndex = 0
            }

            width: tabColumn.width
            height: tabColumn.height * 0.1
        }

        Repeater {
            model: _plugins

            MediaButton {
                text: name
                onClicked: tabColumn.currentIndex = index + 1
                width: tabColumn.width
                height: tabColumn.height * 0.1
            }
        }
    }

    StackLayout {
        id: stack
        currentIndex:  tabColumn.currentIndex
        anchors {
            top: root.top
            left: tabColumn.right
            right: root.right
            leftMargin: root.width * 0.02
        }

        height: root.height

        ColumnLayout {

            GroupBox {
                title: "Language"

                MediaCombobox {

                }
            }

            GroupBox {
                title: "DB"

                MediaCombobox {
                    model: ListModel {
                        ListElement {
                            display: "Json"
                            db: "DataJson"
                        }
                        ListElement {
                            display: "Xml"
                            db: "DataXml"
                        }
                        //                    ListElement {
                        //                        display: "SQL"
                        //                        db: "DataSql"
                        //                    }
                    }

                    textRole: "display"
                    valueRole: "db"
                    currentIndex: -1
                    onCurrentValueChanged: _settings.setDb(currentValue)

                    Component.onCompleted: currentIndex = indexOfValue(_settings.db())
                }
            }

            GroupBox {
                title: "Plugins"

                ColumnLayout {
                    anchors.fill: parent

                    Repeater {
                        model: _plugins

                        MediaCheckbox {
                            text: name
                            checked: enable

                            onCheckedChanged: {
                                enable = checked
                                _settings.setPlugin(name, enable)
                            }
                        }
                    }
                }
            }

            GroupBox {
                title: "Sync"
            }

            GroupBox {
                title: "Stream"
            }
        }

        Repeater {
            model: _plugins

            Loader {
                source: settingsView
            }
        }
    }
}
