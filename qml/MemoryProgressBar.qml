import QtQuick 2.15

Item {
    property double nonCachedNonBufferValue: 0.0
    property double bufferValue: 0.0
    property double cachedValue: 0.0

    property string nonCachedNonBufferColor: "#3399FF"
    property string bufferValueColor: "yellow"
    property string cachedColor: "green"
    property string emptyColor: "lightgray"

    Rectangle{
        id: nonCachedNonBufferRectangle

        height: parent.height
        width: calcCachedNonBufferRectangleWidth();

        color: nonCachedNonBufferColor
        border.color: "black"
        border.width: 2
    }
    Rectangle{
        id: bufferRectangle

        anchors.left: nonCachedNonBufferRectangle.right

        height: parent.height
        width: calcBufferValueRectangleWidth();

        color: bufferValueColor
        border.color: "black"
        border.width: 2
    }
    Rectangle{
        id: cachedRectangle

        anchors.left: bufferRectangle.right

        height: parent.height
        width: calcCachedValueRectangleWidth();

        color: cachedColor
        border.color: "black"
        border.width: 2
    }
    Rectangle{
        id: emptyRectangle

        anchors.left: cachedRectangle.right

        height: parent.height
        width: calcEmptyRectangleWidth();

        color: emptyColor
        border.color: "black"
        border.width: 2
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

        return (bufferValue / 100.0) * width;
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
