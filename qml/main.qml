import QtQuick 2.15
import QtQuick.Window 2.15
import Qt.labs.qmlmodels 1.0
import com.sysmon 1.0

Window {
    id: root

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    readonly property int elementWidth: root.width
    readonly property int elementHeight: 20

    SystemInformation{
        id: sysinfo
    }

    Column{
        id: column

        OSDisplay{
            width: root.elementWidth
            height: root.elementHeight
            osName: sysinfo.operatingSystem
        }
        KernelDisplay{
            width: root.elementWidth
            height: root.elementHeight

            kernelName: sysinfo.kernel
        }
        CPUUtilizationDisplay{
            width: root.elementWidth
            height: root.elementHeight

            progressBarColor: "#3399FF" // blue
            minMaxTextColor: "blue"

            value: sysinfo.cpuUtilizationInPercent
        }
        Repeater{
            model: sysinfo.coreUtilizationsInPercent.length

            CoreUtilizationDisplay{
                width: root.elementWidth
                height: root.elementHeight
                core: index + 1

                value: sysinfo.coreUtilizationsInPercent[index]

                progressBarColor: "#3399FF" // blue
                minMaxTextColor: "blue"
            }
        }
        MemoryDisplay{
            id: memoryDisplay

            width: root.elementWidth
            height: root.elementHeight

            nonCachedNonBufferValue: sysinfo.nonCacheNonBufferMemoryInPercent
            bufferValue: sysinfo.buffersInPercent
            cachedValue: sysinfo.cachedMemoryInPercent
            totalValue: sysinfo.totalUsedMemoryInPercent

            nonCachedNonBufferColor: "#3399FF"
            bufferValueColor: "yellow"
            cachedColor: "green"
            emptyColor: "lightgray"
            minMaxTextColor: "blue"

        }
        SwapDisplay{
            id: swapDisplay

            width: root.elementWidth
            height: root.elementHeight

            progressBarColor: "#FF9933" // orange
            minMaxTextColor: "#FF8000" // orange


            value: sysinfo.swapInPercent
        }
        TotalProcessesDisplay{
            id: totalProcessesDisplay

            width: root.elementWidth
            height: root.elementHeight

            countOfProcesses: sysinfo.totalProcesses
        }
        RunningProcessesDisplay{
            id: runningProcessesDisplay

            width: root.elementWidth
            height: root.elementHeight

            countOfRunningProcesses: sysinfo.runningProcesses
        }
        UpTimeDisplay{
            id: upTimeDisplay

            width: root.elementWidth
            height: root.elementHeight

            upTimeInSeconds: sysinfo.UpTime
        }
    }


    TableView {
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        model: TableModel {
            TableModelColumn { display: "name" }
            TableModelColumn { display: "color" }

            rows: [
                {
                    "name": "cat",
                    "color": "black"
                },
                {
                    "name": "dog",
                    "color": "brown"
                },
                {
                    "name": "bird",
                    "color": "white"
                }
            ]
        }

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            border.width: 1

            Text {
                text: display
                anchors.centerIn: parent
            }
        }
}
