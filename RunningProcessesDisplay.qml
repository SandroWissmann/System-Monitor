import QtQuick 2.15

Rectangle {
    property int countOfRunningProcesses: 0

    Text{
        anchors.fill: parent

        text: "Running Processes: " + parent.countOfRunningProcesses
    }
}
