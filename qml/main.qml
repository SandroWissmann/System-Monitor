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

    readonly property int elementWidth: root.width
    readonly property int elementHeight: 20

//    SystemInformation{
//        id: sysinfo
//    }

//    Column{
//        id: displayColumn

//        OSDisplay{
//            width: root.elementWidth
//            height: root.elementHeight
//            osName: sysinfo.operatingSystem
//        }
//        KernelDisplay{
//            width: root.elementWidth
//            height: root.elementHeight

//            kernelName: sysinfo.kernel
//        }
//        CPUUtilizationDisplay{
//            width: root.elementWidth
//            height: root.elementHeight

//            progressBarColor: "#3399FF" // blue
//            minMaxTextColor: "blue"

//            value: sysinfo.cpuUtilizationInPercent
//        }
//        Repeater{
//            model: sysinfo.coreUtilizationsInPercent.length

//            CoreUtilizationDisplay{
//                width: root.elementWidth
//                height: root.elementHeight
//                core: index + 1

//                value: sysinfo.coreUtilizationsInPercent[index]

//                progressBarColor: "#3399FF" // blue
//                minMaxTextColor: "blue"
//            }
//        }
//        MemoryDisplay{
//            id: memoryDisplay

//            width: root.elementWidth
//            height: root.elementHeight

//            nonCachedNonBufferValue: sysinfo.nonCacheNonBufferMemoryInPercent
//            bufferValue: sysinfo.buffersInPercent
//            cachedValue: sysinfo.cachedMemoryInPercent
//            totalValue: sysinfo.totalUsedMemoryInPercent

//            nonCachedNonBufferColor: "#3399FF"
//            bufferValueColor: "yellow"
//            cachedColor: "green"
//            emptyColor: "lightgray"
//            minMaxTextColor: "blue"

//        }
//        SwapDisplay{
//            id: swapDisplay

//            width: root.elementWidth
//            height: root.elementHeight

//            progressBarColor: "#FF9933" // orange
//            minMaxTextColor: "#FF8000" // orange


//            value: sysinfo.swapInPercent
//        }
//        TotalProcessesDisplay{
//            id: totalProcessesDisplay

//            width: root.elementWidth
//            height: root.elementHeight

//            countOfProcesses: sysinfo.totalProcesses
//        }
//        RunningProcessesDisplay{
//            id: runningProcessesDisplay

//            width: root.elementWidth
//            height: root.elementHeight

//            countOfRunningProcesses: sysinfo.runningProcesses
//        }
//        UpTimeDisplay{
//            id: upTimeDisplay

//            width: root.elementWidth
//            height: root.elementHeight

//            upTimeInSeconds: sysinfo.UpTime
//        }
//    }

    TableView {
        id: tableView

        columnWidthProvider: function (column) { return 100; }

        anchors.fill: parent

        topMargin: columnsHeader.implicitHeight

        model: ProcessTableModel {
            id: processTableModel
        }

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
        }
        clip: true

        delegate: Rectangle {
            implicitWidth: 80
            implicitHeight: 20
            Text {
                text: display
            }
        }

        Rectangle { // mask the headers
            z: 3
            color: "#222222"
            y: tableView.contentY
            x: tableView.contentX
            width: tableView.leftMargin
            height: tableView.topMargin
        }


        Row {
            id: columnsHeader
            y: tableView.contentY
            z: 2
            Repeater {
                model: tableView.columns > 0 ? tableView.columns : 1
                Label {
                    width: tableView.columnWidthProvider(modelData)
                    height: 35
                    text: processTableModel.headerData(modelData, Qt.Horizontal)
                    color: "green"
                    verticalAlignment: Text.AlignVCenter

                    background: Rectangle { color: "#FFFFFF" }
                }
            }
        }

        ScrollIndicator.horizontal: ScrollIndicator { }
    }
}
