import QtQuick 2.15

Item {
    id: root;

    property alias nonCachedNonBufferValue: progressBar.nonCachedNonBufferValue
    property alias bufferValue: progressBar.bufferValue
    property alias cachedValue: progressBar.cachedValue
    required property int totalValue

    property alias nonCachedNonBufferColor: progressBar.nonCachedNonBufferColor
    property alias bufferValueColor: progressBar.bufferValueColor
    property alias cachedColor: progressBar.cachedColor
    property alias emptyColor: progressBar.emptyColor

    property alias minMaxTextColor: maxPercentageText.color

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
    }

    Text{
        id: maxPercentageText

        anchors.left: progressBar.right

        width: 100

        font.pointSize: parent.fontSize

        text: qsTr(parseFloat(totalValue).toFixed(1) + "/100.0% ")
    }

    function calcProgresBarWidth()
    {
        return width - descriptionText.width - minPercentageText.width
            -maxPercentageText.width;
    }
}
