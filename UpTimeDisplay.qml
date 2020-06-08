import QtQuick 2.15

Rectangle {
    property string upTimeString: ""

    Text{
        anchors.fill: parent

        text: "Up Time: " + parent.upTimeString
    }
}
