import QtQuick 2.15

Item {
    property int countOfRunningProcesses: 0

    Text{
        font.pointSize: parent.height - 6

        text: qsTr("Running Processes: " + parent.countOfRunningProcesses)
    }
}
