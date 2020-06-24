import QtQuick 2.15

Item {
    id: root
    required property string kernelName
    property alias fontSize: kernelText.font.pointSize

    Text{
        id: kernelText

        text: qsTr("Kernel: " + root.kernelName)
    }
}
