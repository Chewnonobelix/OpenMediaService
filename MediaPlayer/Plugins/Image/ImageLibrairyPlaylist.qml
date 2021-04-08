import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer.Components 1.0


Frame {
    id: root

    Connections {
        target: _imageLibrairyModel

        function onSizeChanged() {
            _rep.model = _imageLibrairyModel.size
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0
        ScrollView {
            id: _scroll
            clip:true
            Layout.fillHeight: true
            Layout.preferredWidth: root.width * .80

            Row {
                id: _row
                Repeater {
                    id: _rep

                    model: _imageLibrairyModel ? _imageLibrairyModel.size : 0
                    Tumbler {
                        id: _tumb
                        Layout.fillHeight: true
                        Layout.preferredWidth: root.width * .20
                        Connections {
                            target: _imageLibrairyModel

                            function onCurrentIndexChanged(i, j) {
                                if(modelData === i) {
                                    _tumb.currentIndex = j
                                }
                            }
                        }

                        model: if(_imageLibrairyModel) _imageLibrairyModel.modelAt(modelData)

                        onCurrentIndexChanged: {
                            if(_imageLibrairyModel) _imageLibrairyModel.setIndexes(modelData, currentIndex)
                        }
                    }
                }
            }
        }
        MediaList {
            id: _media
            model: _imageLibrairyModel
            Layout.fillHeight: true
            Layout.preferredWidth: root.width * .20

            delegate: MediaListItem {
                text: name + ": " + count

//                onClicked: root.init()
                onDoubleClicked: {
                    _imageLibrairyModel.onDoubleClicked(index)
                }
            }
        }
    }

}
