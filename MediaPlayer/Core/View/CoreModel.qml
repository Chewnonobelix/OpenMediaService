pragma Singleton
import QtQuick 2.15
import MediaPlayer 1.0

QtObject {
    property ListModel typeModel: ListModel {
        id: typeModel
        ListElement {
            name: "Video"
            role: MediaPlayer.Video
        }
        ListElement {
            name: "Audio"
            role: MediaPlayer.Audio
        }
        ListElement {
            name: "Books"
            role: MediaPlayer.Books
        }
        ListElement {
            name: "Comics"
            role: MediaPlayer.Comics
        }
        ListElement {
            name: "Image"
            role: MediaPlayer.Image
        }
    }
}
