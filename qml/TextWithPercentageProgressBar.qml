import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id: root;

    property color progressBarColor: "#3399FF" // blue
    property color minMaxTextColor: "blue"

    property string textString: ""
    property double value: 0.0

    property int fontSize: height - 6

    Text{
        id: descriptionText

        width: 100

        font.pointSize: parent.fontSize

        text: textString
    }

    Text{
        id: minPercentageText

        anchors.left: descriptionText.right

        width: 25

        font.pointSize: parent.fontSize
        color: parent.minMaxTextColor

        text: qsTr("0% ")
    }

    function normalizeValue(value)
    {
        return value/ 100.0;
    }

    ProgressBar {
        id: progressBar

        anchors.left: minPercentageText.right
        value: normalizeValue(root.value)

        style: ProgressBarStyle {
            background: Rectangle {
                radius: 2
                color: "lightgray"
                border.color: "black"
                border.width: 2
                implicitWidth: calcProgresBarWidth();
                implicitHeight: minPercentageText.height
            }
            progress: Rectangle {
                color: root.progressBarColor
                border.color: "black"
                border.width: 2
            }
        }
    }

    Text{
        id: maxPercentageText

        anchors.left: progressBar.right

        width: 100

        font.pointSize: parent.fontSize
        color: root.minMaxTextColor

        text: qsTr(parseFloat(value).toFixed(1) + "/100.0% ")
    }

    function calcProgresBarWidth()
    {
        return width - descriptionText.width - minPercentageText.width
            -maxPercentageText.width;
    }
}
