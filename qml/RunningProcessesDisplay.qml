import QtQuick 2.15

Item {
    id: root

    required property int runningProcessesCount
    property alias fontSize: text.font.pointSize

    Text{
        id: text

        text: qsTr("Running Processes: " + root.runningProcessesCount)
    }
}
