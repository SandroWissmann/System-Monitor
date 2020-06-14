import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import com.sysmon 1.0



Window {
    id: root

    visible: true
    width: 840
    height: 480
    title: qsTr("System Monitor")

    readonly property int systemInformationDisplayHeight: 240;

    SystemInformationDisplay{
        id: systemInformationDisplay

        width: root.width
    }

    ProcessDisplay{
        anchors.top: systemInformationDisplay.bottom

        id: processDisplay

        width: root.width
        height: root.height - systemInformationDisplayHeight;
    }
}
