import QtQuick 2.15

Item {
    id: root

    required property int countOfProcesses
    required property int fontSize

    Text{
        font.pointSize: root.fontSize

        text: qsTr("Total Processes: " + parent.countOfProcesses)
    }
}
