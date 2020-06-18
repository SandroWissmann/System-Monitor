import QtQuick 2.15

Item {
    id: root

    required property string osName
    required property int fontSize

    Text{
        id: osText

        font.pointSize: root.fontSize

        text: qsTr("OS: " + root.osName)
    }
}

