import QtQuick 2.15

Rectangle {
    property string kernelName: ""


    Text{
        anchors.fill: parent

        text: "Kernel: " + parent.kernelName
    }
}
