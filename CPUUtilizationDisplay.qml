import QtQuick 2.15

Item {
    id: root
    property double value: 0.0

    TextWithPercentageProgressBar{
        id: utilizationProgressBar

        height: root.height

        textString: "CPU"
        value: root.value
    }
}
