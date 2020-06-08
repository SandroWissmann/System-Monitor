import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Column{
        OSDisplay{
            osName: "Kde Neon User Edition"
        }
        KernelDisplay{
            kernelName: "Kernel: 5.3.0-51-generic"
        }
        CPUUtilizationDisplay{
            // add bars here
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

        }
        SwapDisplay{

        }
        TotalProcessesDisplay{
            countOfProcesses: 89784
        }
        RunningProcessesDisplay{
            countOfRunningProcesses: 3
        }
        UpTimeDisplay{
            upTimeString: "33:08:17"
        }
    }
}
