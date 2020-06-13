import QtQuick 2.15

import com.sysmon 1.0

Item {
    id: root

    readonly property int elementWidth: root.width
    readonly property int elementHeight: 20

    SystemInformation{
        id: sysinfo
    }

    Column{
        id: displayColumn

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
}
