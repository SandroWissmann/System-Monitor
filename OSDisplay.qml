import QtQuick 2.15

Rectangle {
    property string osName: ""


    Text{
        anchors.fill: parent

        text: "OS: " + parent.osName
    }
}

