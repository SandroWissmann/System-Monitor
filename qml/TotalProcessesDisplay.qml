import QtQuick 2.15

Item {
    id: root

    property int countOfProcesses: 0
    property int fontSize: height - 6

    Text{
        font.pointSize: root.fontSize

        text: qsTr("Total Processes: " + parent.countOfProcesses)
    }
}
