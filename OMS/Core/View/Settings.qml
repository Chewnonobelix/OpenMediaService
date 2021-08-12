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
            text: qsTr("General")
            onClicked: {
                tabColumn.currentIndex = 0
            }

            autoExclusive: true
            width: tabColumn.width
            height: tabColumn.height * 0.1
            checkable: true
            checked: true
        }

        Repeater {
            model: _plugins

            MediaButton {
                text: name
                onClicked: tabColumn.currentIndex = index + 1
                width: tabColumn.width
                height: tabColumn.height * 0.1
                autoExclusive: true
                checkable: true
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
                title: qsTr("Language")

                MediaCombobox {
                    Component.onCompleted: {
                        model = _language.languageList()
                        currentIndex = indexOfValue(_settings.language())
                    }

                    onActivated: _settings.setLanguage(currentText)
                }
            }

            GroupBox {
                title: "DB"

                MediaCombobox {
                    model: ListModel {
                        ListElement {
                            display: qsTr("Json")
                            db: "DataJson"
                        }
                        ListElement {
                            display: qsTr("Xml")
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
                    onActivated: _settings.setDb(currentValue)

                    Component.onCompleted: currentIndex = indexOfValue(_settings.db())
                }
            }

            GroupBox {
                title: qsTr("Plugins")

                ColumnLayout {
                    anchors.fill: parent

                    Repeater {
                        model: _plugins

                        MediaCheckbox {
                            text: name
                            checked: enable

                            onClicked: {
                                enable = checked
                                _settings.setPlugin(name, enable)
                            }
                        }
                    }
                }
            }

            GroupBox {
                title: qsTr("Sync")
            }

            GroupBox {
                title: qsTr("Stream")
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
