import QtQuick 2.15

Item {
    id: root
    property double value: 0.0

    required property string progressBarColor
    required property string minMaxTextColor
    required property int fontSize

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
