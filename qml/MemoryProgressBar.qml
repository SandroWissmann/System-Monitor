import QtQuick 2.15

Item {
    required property double nonCachedNonBufferValue
    required property double bufferValue
    required property double cachedValue

    required property color nonCachedNonBufferColor
    required property color bufferValueColor
    required property color cachedColor
    required property color emptyColor

    readonly property int itemBorderWidth: 2

    Rectangle{
        id: nonCachedNonBufferRectangle

        height: parent.height
        width: calcCachedNonBufferRectangleWidth() + itemBorderWidth;

        color: nonCachedNonBufferColor
        border.color: "black"
        border.width: itemBorderWidth
    }
    Rectangle{
        id: bufferRectangle

        anchors.left: nonCachedNonBufferRectangle.right
        anchors.leftMargin: -itemBorderWidth

        height: parent.height
        width: calcBufferValueRectangleWidth() + itemBorderWidth;

        color: bufferValueColor
        border.color: "black"
        border.width: itemBorderWidth
    }
    Rectangle{
        id: cachedRectangle

        anchors.left: bufferRectangle.right
        anchors.leftMargin: -itemBorderWidth

        height: parent.height
        width: calcCachedValueRectangleWidth() + itemBorderWidth;

        color: cachedColor
        border.color: "black"
        border.width: itemBorderWidth
    }
    Rectangle{
        id: emptyRectangle

        anchors.left: cachedRectangle.right
        anchors.leftMargin: -itemBorderWidth

        height: parent.height
        width: calcEmptyRectangleWidth() + 3 * itemBorderWidth;

        color: emptyColor
        border.color: "black"
        border.width: itemBorderWidth
    }

    function calcCachedNonBufferRectangleWidth()
    {
        console.assert(nonCachedNonBufferValue >= 0.0,
                       "nonCachedNonBufferValue < 0.0");
        console.assert(nonCachedNonBufferValue <= 100.0,
                       "nonCachedNonBufferValue > 100.0");

        return (nonCachedNonBufferValue / 100.0) * width;
    }

    function calcBufferValueRectangleWidth()
    {
        console.assert(bufferValue >= 0.0,
                       "bufferValue < 0.0");
        console.assert(bufferValue <= 100.0,
                       "bufferValue > 100.0");

        return (bufferValue / 100.0) * width;
    }

    function calcCachedValueRectangleWidth()
    {
        console.assert(cachedValue >= 0.0,
                       "cachedValue < 0.0");
        console.assert(cachedValue <= 100.0,
                       "cachedValue > 100.0");

        return (cachedValue / 100.0) * width;
    }

    function calcEmptyRectangleWidth()
    {
        var emptyValue = width;
        emptyValue -= nonCachedNonBufferRectangle.width;
        emptyValue -= bufferRectangle.width;
        emptyValue -= cachedRectangle.width;

        return emptyValue;
    }
}
