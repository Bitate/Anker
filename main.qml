import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: "Anker"
    visible: true
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

    ListView {
        id: listView
        visible: false
        x: 245
        y: 160
        width: 110
        height: 160

        // TODO: display Anki deck names
        model: {

        }

        delegate: Item {
            x: 5
            width: 80
            height: 40
            Row {
                id: row1
                spacing: 10
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                }

                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.3300000429153442;height:480;width:640}
}
##^##*/
