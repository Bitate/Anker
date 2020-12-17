import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: applicationWindow
    title: "Anker"
    visible: true
    width: 420
    height: 520

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
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 84
        anchors.leftMargin: 85
        anchors.bottomMargin: 128
        anchors.topMargin: 100

        model: Anker.deck_name_list_model

        delegate: Component {
            CheckBox {
                text: display
                onCheckedChanged: Anker.import_deck_name = display
            }
        }
    }

    Label {
        id: deck_name_label
        text: qsTr("All Decks")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 451
        anchors.rightMargin: 156
        anchors.leftMargin: 156
        anchors.topMargin: 40
        font.pointSize: 18
        minimumPixelSize: 12
    }

    Button {
        id: open_files_button
        text: qsTr("Open")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 411
        anchors.bottomMargin: 75
        anchors.rightMargin: 164
        anchors.leftMargin: 165
        onClicked: {
            open_files_dialog.open()
        }
    }
}



