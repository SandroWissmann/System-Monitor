import QtQuick 2.15

Item {
    id: root
    required property string kernelName
    required property int fontSize

    Text{
        id: kernelText

        font.pointSize: root.fontSize

        text: qsTr("Kernel: " + root.kernelName)
    }
}
