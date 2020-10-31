import QtQuick 2.15

Rectangle {
    property alias text: text.text

    implicitHeight: 20

    Text {
        id: text
        anchors.fill: parent
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter

        color: "green"
    }
}
