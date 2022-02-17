import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MediaPlayer 1.0
import MediaPlayer.Model 1.0
import MediaPlayer.Components 1.0

SplitView {
    id: splitView
    orientation: Qt.Horizontal

    function idList () {
        var ret = [];

        for(var i = 0; i < count; i++) {
            ret[i] = itemAt(i).idTab
        }

        return ret
    }

    property var component;
    property var sprite;

    function onClicked(index) {
        setCurrentIndex(index)
    }

    function addNew() {
        component = Qt.createComponent("View.qml");
        if (component.status === Component.Ready)
            finishCreation();
        else
            component.statusChanged.connect(finishCreation);

    }

    function removeView(idTab) {
        var ret = _tabWrapper.removeManager(idTab)
        console.log("Remove view", ret)

        if(ret) {
            takeItem(currentIndex)

            for(var i = 0; i < count; i++) {
                itemAt(i).index = i
            }

            setCurrentIndex(0)
        }
    }

    function createWindow() {
        _tabWrapper.createWindow()
    }

    function finishCreation() {
        if (component.status === Component.Ready) {
            sprite = component.createObject(this, {});
            if (sprite === null) {
                // Error Handling
                console.log("Error creating object");
            }
            else {
                addItem(sprite)
                sprite.index = count - 1
                sprite.clicked.connect(onClicked)
                sprite.newView.connect(addNew)
                sprite.remove.connect(removeView)
                sprite.newWindow.connect(createWindow)
            }
        } else if (component.status === Component.Error) {
            // Error Handling
            console.log("Error loading component:", component.errorString());
        }
    }


    Component.onCompleted:  {
        addNew()
    }
}
