import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import com.sysmon 1.0



Window {
    id: root

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Column{
        SystemInformationDisplay{
            id: systemInformationDisplay

            width: root.width
            height: root.height / 2
        }

        ProcessDisplay{
            id: processDisplay

            width: root.width
            height: root.height / 2
        }
    }
}
