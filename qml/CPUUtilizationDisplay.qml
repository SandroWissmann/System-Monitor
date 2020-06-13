import QtQuick 2.15

Item {
    id: root

    property double value: 0.0

    property string progressBarColor: "black"
    property string minMaxTextColor: "black"
    property int fontSize: height - 6

    TextWithPercentageProgressBar{
        id: utilizationProgressBar

        progressBarColor: parent.progressBarColor
        minMaxTextColor: parent.minMaxTextColor

        height: root.height
        width: root.width

        textString: qsTr("CPU: ")
        value: root.value
        fontSize: root.fontSize
    }
}
