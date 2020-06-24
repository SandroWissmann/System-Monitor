import QtQuick 2.15

Item {
    id: root

    required property string osName
    property alias fontSize: osText.font.pointSize

    Text{
        id: osText

        text: qsTr("OS: " + root.osName)
    }
}

