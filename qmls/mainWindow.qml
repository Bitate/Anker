import QtQml 2.12
import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: rectangle
    x: 220
    y: 140
    width: 200
    height: 200
    color: "green"

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {

            if(mouse.button == Qt.LeftButton)
                parent.color = "blue"
            else
                parent.color = "red"
        }
    }
}
