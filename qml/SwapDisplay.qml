import QtQuick 2.15

Item {
    id: root
    property double value: 0.0

    property string progressBarColor: "black"
    property string minMaxTextColor: "black"

    TextWithPercentageProgressBar{
        id: swapProgressBar

        progressBarColor: parent.progressBarColor
        minMaxTextColor: parent.minMaxTextColor

        height: root.height
        width: root.width

        textString: qsTr("Swap: ")
        value: root.value
    }
}
