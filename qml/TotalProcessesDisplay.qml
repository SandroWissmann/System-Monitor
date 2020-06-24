import QtQuick 2.15

Item {
    id: root

    required property int countOfProcesses
    property alias fontSize: text.font.pointSize

    Text{
        id: text

        font.pointSize: root.fontSize

        text: qsTr("Total Processes: " + parent.countOfProcesses)
    }
}
