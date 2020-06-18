import QtQuick 2.15

Item {
    id: root;

    required property double nonCachedNonBufferValue
    required property double bufferValue
    required property double cachedValue
    required property double totalValue

    required property color nonCachedNonBufferColor
    required property color bufferValueColor
    required property color cachedColor
    required property color emptyColor

    required property color minMaxTextColor

    required property int fontSize


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
