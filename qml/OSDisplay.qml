import QtQuick 2.15

Item {
    property string osName: ""

    Text{
        id: osText

        font.pointSize: parent.height - 6

        text: qsTr("OS: " + parent.osName)
    }
}

