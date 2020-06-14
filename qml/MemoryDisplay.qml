import QtQuick 2.15

Item {
    id: root;

    property string minMaxTextColor: "blue"

    property double nonCachedNonBufferValue: 0.0
    property double bufferValue: 0.0
    property double cachedValue: 0.0
    property double totalValue: 0.0

    property string nonCachedNonBufferColor: "#3399FF"
    property string bufferValueColor: "yellow"
    property string cachedColor: "green"
    property string emptyColor: "lightgray"

    property int fontSize: height - 6


    Text{
        id: descriptionText

        width: 100

        font.pointSize: parent.fontSize

        text: qsTr("Memory: ")
    }

    Text{
        id: minPercentageText

        anchors.left: descriptionText.right

        width: 25

        font.pointSize: parent.fontSize
        color: root.minMaxTextColor

        text: qsTr("0% ")
    }

    MemoryProgressBar{
        id: progressBar

        anchors.left: minPercentageText.right

        implicitWidth: calcProgresBarWidth()
        implicitHeight: minPercentageText.height

        nonCachedNonBufferValue: parent.nonCachedNonBufferValue
        bufferValue: parent.bufferValue
        cachedValue: parent.cachedValue

        nonCachedNonBufferColor: parent.nonCachedNonBufferColor
        bufferValueColor: parent.bufferValueColor
        cachedColor: parent.cachedColor
        emptyColor: parent.emptyColor
    }

    Text{
        id: maxPercentageText

        anchors.left: progressBar.right

        width: 100

        font.pointSize: parent.fontSize
        color: root.minMaxTextColor

        text: qsTr(parseFloat(totalValue).toFixed(1) + "/100.0% ")
    }

    function calcProgresBarWidth()
    {
        return width - descriptionText.width - minPercentageText.width
            -maxPercentageText.width;
    }
}