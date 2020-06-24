import QtQuick 2.15

Item {
    id: root
    property alias value: swapProgressBar.value

    property alias progressBarColor: swapProgressBar.progressBarColor
    property alias minMaxTextColor: swapProgressBar.minMaxTextColor
    property alias fontSize: swapProgressBar.fontSize

    TextWithPercentageProgressBar{
        id: swapProgressBar

        height: root.height
        width: root.width

        textString: qsTr("Swap: ")
    }
}
