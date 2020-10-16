pragma Singleton
import QtQuick 2.15
import MediaPlayer 1.0

QtObject {
    property ListModel typeModel: ListModel {
        id: typeModel
        ListElement {
            name: "Video"
            role: MediaPlayer.MediaRole.Video
        }
        ListElement {
            name: "Audio"
            role: MediaPlayer.MediaRole.Audio
        }
        ListElement {
            name: "Books"
            role: MediaPlayer.MediaRole.Books
        }
        ListElement {
            name: "Comics"
            role: MediaPlayer.MediaRole.Comics
        }
        ListElement {
            name: "Image"
            role: MediaPlayer.MediaRole.Image
        }
    }
}
