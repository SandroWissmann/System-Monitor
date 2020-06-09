import QtQuick 2.15

Item {
    property double value: 0.0

    property string progressBarColor: "black"
    property string minMaxTextColor: "black"

    TextWithPercentageProgressBar{
        id: utilizationProgressBar

        progressBarColor: parent.progressBarColor
        minMaxTextColor: parent.minMaxTextColor

        height: parent.height

        textString: "CPU: "
        value: parent.value
    }
}
