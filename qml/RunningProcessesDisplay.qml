import QtQuick 2.15

Item {
    id: root

    required property int runningProcessesCount
    required property int fontSize

    Text{
        font.pointSize: root.fontSize

        text: qsTr("Running Processes: " + root.runningProcessesCount)
    }
}
