import QtQuick 2.15

Item {
    id: root
    property string kernelName: ""
    property int fontSize: height - 6

    Text{
        id: kernelText

        font.pointSize: root.fontSize

        text: qsTr("Kernel: " + root.kernelName)
    }
}
