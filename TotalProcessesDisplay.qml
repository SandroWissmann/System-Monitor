import QtQuick 2.15

Rectangle {
    property int countOfProcesses: 0

    Text{
        anchors.fill: parent

        text: "Total Processes: " + parent.countOfProcesses
    }
}
