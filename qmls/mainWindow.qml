import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtMultimedia 5.12

ApplicationWindow {
    id: applicationWindow
    visible: true
    height: 600
    width: 1000

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&New...")
            }
            Action {
                text: qsTr("&Open...")
                onTriggered: fileExplorer.open()
            }
            Action {
                text: qsTr("&Save")
            }
            Action {
                text: qsTr("Save &As...")
            }
            Action {
                text: qsTr("&Quit")
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: qsTr("&Edit")
            Action {
                text: qsTr("Cu&t")
            }
            Action { text: qsTr("&Copy") }
            Action { text: qsTr("&Paste") }
        }
        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&About") }
        }
    }


    Slider {
        id: playProgressBar
        x: 0
        y: 550
        width: 827
        height: 25
        anchors.verticalCenter: volumeSlider.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: videoOutputContainer.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 35
        anchors.topMargin: 15
        anchors.rightMargin: 180
        value: mediaPlayer.position / mediaPlayer.duration

        onMoved: {
            mediaPlayer.seek( mediaPlayer.duration * playProgressBar.position)
        }
    }

    Rectangle {
        id: videoOutputContainer
        x: 0
        y: 0
        width: applicationWindow.width
        color: "#101010"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 76
        anchors.leftMargin: 0
        anchors.topMargin: -6

        VideoOutput {
            id: videoOutput
            x: 0
            y: 0
            width: 188
            height: 316
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            source: mediaPlayer
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }

    MediaPlayer {
        id: mediaPlayer
        source: fileExplorer.fileUrl
        volume: volumeSlider.volume
    }

    FileDialog {
        id: fileExplorer
        title: "Please choose a file"
        folder: shortcuts.home + "/Music"
        onAccepted: mediaPlayer.playlist.addItem(fileExplorer.fileUrl)
    }

    Slider {
        id: volumeSlider
        anchors.left: playProgressBar.right
        anchors.right: parent.right
        anchors.top: videoOutputContainer.bottom
        anchors.bottom: parent.bottom
        anchors.rightMargin: 12
        anchors.topMargin: 19
        anchors.leftMargin: 12
        anchors.bottomMargin: 39
        touchDragThreshold: 0

        value: 1

        from: 0
        to: 1

        property real volume: QtMultimedia.convertVolume(volumeSlider.value, QtMultimedia.LogarithmicVolumeScale, QtMultimedia.LinearVolumeScale)
        x: 826
        y: 530
        width: 166
        height: 27
    }

    Button {
        id: playButton
        width: 50
        text: qsTr("Play")
        anchors.left: parent.left
        anchors.top: playProgressBar.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 6

        onClicked: mediaPlayer.play()
    }

    Button {
        id: pauseButton
        width: 47
        text: qsTr("Pause")
        anchors.left: playButton.right
        anchors.top: playProgressBar.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.topMargin: 6
        anchors.leftMargin: 1

        onClicked: mediaPlayer.pause()
    }

    Button {
        id: previousButton
        width: 50
        text: qsTr("Prev")
        anchors.left: pauseButton.right
        anchors.top: playProgressBar.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        anchors.bottomMargin: 0
        anchors.topMargin: 6
        onClicked: mediaPlayer.playlist.previous()
    }

    Button {
        id: nextButton
        width: 50
        text: qsTr("Next")
        anchors.left: previousButton.right
        anchors.top: playProgressBar.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.topMargin: 6
        anchors.leftMargin: -1
        onClicked: mediaPlayer.playlist.next()
    }

    Button {
        id: openButton
        width: 50
        text: qsTr("Open")
        anchors.left: nextButton.right
        anchors.top: playProgressBar.bottom
        anchors.bottom: parent.bottom
        display: AbstractButton.TextBesideIcon
        anchors.bottomMargin: 0
        anchors.topMargin: 6
        anchors.leftMargin: -1

        onClicked: fileExplorer.open()
    }
}










