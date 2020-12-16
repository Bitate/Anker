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
                onTriggered: open_files_dialog.open()
            }

            Action {
                text: qsTr("&TODO")
            }

            Action {
                text: qsTr("&Quit")
                onTriggered: Qt.quit()
            }
        }
    }

    FileDialog {
        id: open_files_dialog
        selectMultiple: true
        onAccepted: {
            Anker.file_urls = open_files_dialog.fileUrls
        }
    }

    MessageDialog {
        id: on_chosen_message_dialog

        title: "You have chosen deck:"
        text: "Deck name goes here "
    }

    ListView {
        id: deck_name_list_view
        x: 50
        y: 78
        width: 380
        height: 352

        model: Anker.deck_name_list_model

        delegate: Component {
            Text {
                text: display
            }
        }
    }

    Label {
        id: deck_name_label
        x: 186
        y: 43
        width: 108
        height: 29
        text: qsTr("All Decks")
        font.pointSize: 18
        minimumPixelSize: 12
    }

    Button {
        id: open_files_button
        x: 190
        y: 436
        text: qsTr("Open")
        onClicked: {
            open_files_dialog.open()
        }
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
