import QtQuick 2.15

Item {
    id: root

    property double value: 0.0

    property string progressBarColor: "black"
    property string minMaxTextColor: "black"

    TextWithPercentageProgressBar{
        id: utilizationProgressBar

        progressBarColor: parent.progressBarColor
        minMaxTextColor: parent.minMaxTextColor

        height: root.height

        textString: qsTr("CPU: ")
        value: root.value
    }
}
