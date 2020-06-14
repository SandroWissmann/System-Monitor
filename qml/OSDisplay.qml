import QtQuick 2.15

Item {
    id: root

    property string osName: ""
    property int fontSize: height - 6

    Text{
        id: osText

        font.pointSize: root.fontSize

        text: qsTr("OS: " + root.osName)
    }
}

