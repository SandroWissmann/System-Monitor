import QtQuick 2.15

Item {
    property string upTimeString: ""

    Text{
        font.pointSize: parent.height - 6

        text: "Up Time: " + parent.upTimeString
    }
}
