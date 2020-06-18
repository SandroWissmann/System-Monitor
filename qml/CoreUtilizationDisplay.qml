import QtQuick 2.15

Item {
    id: root

    property double value: 0.0

    property int core: 1

    property color progressBarColor: "black"
    property color minMaxTextColor: "black"
    property int fontSize: height - 6

    TextWithPercentageProgressBar{
        id: utilizationProgressBar

        progressBarColor: root.progressBarColor
        minMaxTextColor: root.minMaxTextColor

        height: root.height
        width: root.width

        textString: qsTr("Core" + core + ": ")
        value: root.value

        fontSize: root.fontSize
    }
}
