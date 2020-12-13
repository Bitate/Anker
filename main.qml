import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: "Anker"
    visible: true;
    width: 1024
    height: 768

    menuBar: MenuBar {
        Menu {
            title: "&File"

            Action {
                text: qsTr("&Open...")
                onTriggered: openFolderDialog.open()
            }

            Action {
                text: qsTr("&Quit")
                onTriggered: Qt.quit()
            }
        }
    }

    FileDialog {
        id: openFolderDialog
        // selectFolder: true
        selectMultiple: true
        onAccepted: {
            Anker.file_urls = openFolderDialog.fileUrls
        }
    }

    Button {
        id: button
        x: 382
        y: 321
        width: 260
        height: 127
        text: qsTr("Start Processing")
    }



}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
