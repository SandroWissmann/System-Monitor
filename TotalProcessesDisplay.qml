import QtQuick 2.15

Item {
    property int countOfProcesses: 0

    Text{
        font.pointSize: parent.height - 6

        text: "Total Processes: " + parent.countOfProcesses
    }
}
