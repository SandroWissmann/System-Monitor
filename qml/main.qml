import QtQuick 2.15
//import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Window 2.15
import com.sysmon 1.0

Window {
    id: root

    visible: true
    width: 840
    height: 480
    title: qsTr("System Monitor")

    ColumnLayout{

        SystemInformationDisplay{
            id: systemInformationDisplay

            Layout.preferredHeight: systemInformationDisplay.systemHeight
            Layout.preferredWidth: root.width
        }

        ProcessDisplay{
            id: processDisplay

            Layout.preferredHeight: root.height -
                                    systemInformationDisplay.height;
            Layout.preferredWidth: root.width
        }
    }
}
