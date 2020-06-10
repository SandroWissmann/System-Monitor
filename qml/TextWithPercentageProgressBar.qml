import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id: root;

    property string progressBarColor: "#3399FF" // blue
    property string minMaxTextColor: "blue"

    property string textString: ""
    property double value: 50.0

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
        color: root.minMaxTextColor

        text: "0% "
    }

    ProgressBar {
        id: progressBar

        anchors.left: minPercentageText.right
        value: root.value

        style: ProgressBarStyle {
            background: Rectangle {
                radius: 2
                color: "lightgray"
                border.color: "black"
                border.width: 2
                implicitWidth: 300
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

        font.pointSize: parent.fontSize
        color: root.minMaxTextColor

        text: parseFloat(value).toFixed(1) + "/100.0% "
    }
}
