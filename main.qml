import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4
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
        id: deckNameListView
        x: 50
        y: 78
        width: 380
        height: 352

        model: Anker.deck_name_list_model

        delegate: Text {
            // TODO: weird "display"
            text: display
        }
    }

    Label {
        id: deckNameLabel
        x: 186
        y: 43
        width: 108
        height: 29
        text: qsTr("All Decks")
        font.pointSize: 18
        minimumPixelSize: 12
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
