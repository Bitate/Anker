import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtMultimedia 5.12


ApplicationWindow {
    Slider {
        id: volume
        x: 444
        y: 373
        width: 167
        height: 25
        touchDragThreshold: 0
        value: 0.5
    }

    RoundButton {
        id: playAudioButton
        x: 312
        y: 365
        text: "Play"
    }

    Slider {
        id: progressBar
        x: 41
        y: 373
        width: 174
        height: 25
        value: 0.5
    }

    Audio {
        id: audioPlayer
        source: fileExplorer.fileUrl
    }

    FileDialog {
        id: fileExplorer
        onFileUrlsChanged: {
            console.log("Open: " + fileExplorer.fileUrl)
        }

        onRejected: {
            console.log("Cancel choose file")
        }
    }

    ToolButton {
        id: toolButton
        x: 0
        y: 0
        text: qsTr("Open")
        onClicked: fileExplorer.open()
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.8999999761581421;height:480;width:640}
}
##^##*/
