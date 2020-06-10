import QtQuick 2.15

Item {
    id: root

    property double value: 0.0

    property int core: 1

    property string progressBarColor: "black"
    property string minMaxTextColor: "black"

    TextWithPercentageProgressBar{
        id: utilizationProgressBar

        progressBarColor: root.progressBarColor
        minMaxTextColor: root.minMaxTextColor

        height: root.height

        textString: "Core" + core + ": "
        value: root.value
    }
}
