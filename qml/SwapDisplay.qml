import QtQuick 2.15

Item {
    id: root
    property double value: 0.0

    property string progressBarColor: "black"
    property string minMaxTextColor: "black"
    property int fontSize: height - 6

    TextWithPercentageProgressBar{
        id: swapProgressBar

        progressBarColor: parent.progressBarColor
        minMaxTextColor: parent.minMaxTextColor

        height: root.height
        width: root.width
        fontSize: root.fontSize

        textString: qsTr("Swap: ")
        value: root.value
    }
}
