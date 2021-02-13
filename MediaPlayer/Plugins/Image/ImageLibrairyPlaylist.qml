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

	property string path

	RowLayout {
		anchors.fill: parent
		spacing: 0
		ScrollView {
			Layout.fillHeight: true
			Layout.preferredWidth: root.width * .80
			clip:true
			Row {
			Repeater {
				id: _rep

				Tumbler {
					id: _tumb
					Layout.fillHeight: true
					Layout.preferredWidth: root.width * .20
					Connections {
						target: _imageLibrairyModel

						function onIndexesChanged(index, list) {
							if(modelData === index) {
								_tumb.model = list
							}
						}

						function onCurrentIndexChanged(i, j) {
							if(modelData === i) {
								_tumb.currentIndex = j
							}
						}
					}

					model: _imageLibrairyModel.modelAt(modelData)

					//				property string currentModel: model[currentIndex]

					onCurrentIndexChanged: {
						_imageLibrairyModel.setIndexes(modelData, currentIndex)
					}
				}
		}
			}
		}
		MediaList {
			model: _imageLibrairyModel
			Layout.fillHeight: true
			Layout.preferredWidth: root.width * .20

			delegate: MediaListItem {
				text: name + ": " + count

				onDoubleClicked: {
					_imageLibrairyModel.onDoubleClicked(index)
				}
			}
		}
	}

}
