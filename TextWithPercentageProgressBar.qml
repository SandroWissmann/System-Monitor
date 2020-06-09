import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id: root;

    property string textString: ""
    property double min: 0.0
    property double max: 100.0
    property double value: 50.0

    property int fontSize: 15

    function calcProgressBarValue(min, max, value) {
        return value / (max - min);
    }

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
        color: "blue"

        text: parseInt(min) + "% "
    }

    ProgressBar {
        id: progressBar

        anchors.left: minPercentageText.right
        value: calcProgressBarValue(root.min, root.max, root.value);

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
                color: "#3399FF" //blue
                border.color: "black"
                border.width: 2
            }
        }
    }

    Text{
        id: maxPercentageText

        anchors.left: progressBar.right

        font.pointSize: parent.fontSize
        color: "blue"

        text: parseFloat(value).toFixed(1) + "/" + parseFloat(max).toFixed(1) + "% "
    }
}
