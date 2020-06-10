import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: root

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    readonly property int elementWidth: root.width
    readonly property int elementHeight: 20

    Column{

        OSDisplay{
            width: root.elementWidth
            height: root.elementHeight

            osName: "Kde Neon User Edition"
        }
        KernelDisplay{
            width: root.elementWidth
            height: root.elementHeight

            kernelName: "5.3.0-51-generic"
        }
        CPUUtilizationDisplay{
            width: root.elementWidth
            height: root.elementHeight

            progressBarColor: "#3399FF" // blue
            minMaxTextColor: "blue"

            value: 50.0
        }
        CoreUtilizationDisplay{
            width: root.elementWidth
            height: root.elementHeight
            core: 1

            progressBarColor: "#3399FF" // blue
            minMaxTextColor: "blue"
        }
        CoreUtilizationDisplay{
            width: root.elementWidth
            height: root.elementHeight
            core: 2

            progressBarColor: "#3399FF" // blue
            minMaxTextColor: "blue"
        }
        CoreUtilizationDisplay{
            width: root.elementWidth
            height: root.elementHeight
            core: 3

            progressBarColor: "#3399FF" // blue
            minMaxTextColor: "blue"
        }
        CoreUtilizationDisplay{
            width: root.elementWidth
            height: root.elementHeight
            core: 4

            progressBarColor: "#3399FF" // blue
            minMaxTextColor: "blue"
        }
        MemoryDisplay{
            width: root.elementWidth
            height: root.elementHeight

            nonCachedNonBufferValue: 60
            bufferValue: 15
            cachedValue: 10

            nonCachedNonBufferColor: "#3399FF"
            bufferValueColor: "yellow"
            cachedColor: "green"
            emptyColor: "lightgray"
            minMaxTextColor: "blue"

        }
        SwapDisplay{
            width: root.elementWidth
            height: root.elementHeight

            progressBarColor: "#FF9933" // orange
            minMaxTextColor: "#FF8000" // orange

            value: 70
        }
        TotalProcessesDisplay{
            width: root.elementWidth
            height: root.elementHeight

            countOfProcesses: 89784
        }
        RunningProcessesDisplay{
            width: root.elementWidth
            height: root.elementHeight

            countOfRunningProcesses: 3
        }
        UpTimeDisplay{
            width: root.elementWidth
            height: root.elementHeight

            upTimeString: "33:08:17"
        }
    }
}
