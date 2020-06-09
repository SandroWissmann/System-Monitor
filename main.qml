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

            value: 50.0
        }
//        Text{
//            text: "Core 1: "
//        }
//        Text{
//            text: "Core 2:"
//        }
//        Text{
//            text: "Core 3:"
//        }
//        Text{
//            text: "Core 4:"
//        }
        MemoryDisplay{
            width: root.elementWidth
            height: root.elementHeight
        }
        SwapDisplay{
            width: root.elementWidth
            height: root.elementHeight
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
