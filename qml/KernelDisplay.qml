import QtQuick 2.15

Item {
    id: root
    property string kernelName: ""

    Text{
        id: kernelText

        font.pointSize: parent.height - 6

        text: "Kernel: " + parent.kernelName
    }
}
