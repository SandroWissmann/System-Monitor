import QtQuick 2.15

Item {
    id: root

    property alias value: utilizationProgressBar.value

    property int core: 1

    property alias progressBarColor: utilizationProgressBar.progressBarColor
    property alias minMaxTextColor: utilizationProgressBar.minMaxTextColor
    property alias fontSize: utilizationProgressBar.fontSize

    TextWithPercentageProgressBar{
        id: utilizationProgressBar

        height: root.height
        width: root.width

        textString: qsTr("Core" + core + ": ")
    }
}
