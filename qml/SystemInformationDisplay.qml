import QtQuick 2.15

import com.sysmon 1.0

Item {
    id: root

    height: (8 + sysinfo.coreUtilizationsInPercent.length) * elementHeight

    readonly property int elementWidth: root.width
    readonly property int elementHeight: 20
    property int fontSize: elementHeight - 8

    SystemInformation{
        id: sysinfo
    }

    Column{
        id: displayColumn

        OSDisplay{
            width: root.elementWidth
            height: root.elementHeight
            fontSize: root.fontSize

            osName: sysinfo.operatingSystem
        }
        KernelDisplay{
            width: root.elementWidth
            height: root.elementHeight
            fontSize: root.fontSize

            kernelName: sysinfo.kernel
        }
        CPUUtilizationDisplay{
            width: root.elementWidth
            height: root.elementHeight
            fontSize: root.fontSize

            progressBarColor: "#3399FF" // blue
            minMaxTextColor: "blue"

            value: sysinfo.cpuUtilizationInPercent
        }
        Repeater{
            model: sysinfo.coreUtilizationsInPercent.length

            CoreUtilizationDisplay{
                width: root.elementWidth
                height: root.elementHeight
                fontSize: root.fontSize

                progressBarColor: "#3399FF" // blue
                minMaxTextColor: "blue"

                core: index + 1
                value: sysinfo.coreUtilizationsInPercent[index]
            }
        }
        MemoryDisplay{
            id: memoryDisplay

            width: root.elementWidth
            height: root.elementHeight
            fontSize: root.fontSize

            nonCachedNonBufferColor: "#3399FF"
            bufferValueColor: "yellow"
            cachedColor: "green"
            emptyColor: "lightgray"
            minMaxTextColor: "blue"

            nonCachedNonBufferValue: sysinfo.nonCacheNonBufferMemoryInPercent
            bufferValue: sysinfo.buffersInPercent
            cachedValue: sysinfo.cachedMemoryInPercent
            totalValue: sysinfo.totalUsedMemoryInPercent

        }
        SwapDisplay{
            id: swapDisplay

            width: root.elementWidth
            height: root.elementHeight
            fontSize: root.fontSize

            progressBarColor: "#FF9933" // orange
            minMaxTextColor: "#FF8000" // orange

            value: sysinfo.swapInPercent
        }
        TotalProcessesDisplay{
            id: totalProcessesDisplay

            width: root.elementWidth
            height: root.elementHeight
            fontSize: root.fontSize

            countOfProcesses: sysinfo.totalProcesses
        }
        RunningProcessesDisplay{
            id: runningProcessesDisplay

            width: root.elementWidth
            height: root.elementHeight
            fontSize: root.fontSize

            countOfRunningProcesses: sysinfo.runningProcesses
        }
        UpTimeDisplay{
            id: upTimeDisplay

            width: root.elementWidth
            height: root.elementHeight
            fontSize: root.fontSize

            upTimeInSeconds: sysinfo.UpTime
        }
    }
}
