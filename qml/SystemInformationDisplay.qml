/* System Monitor
 * Copyright (C) 2020  Sandro Wißmann
 *
 * Minefield is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Minefield is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with System Monitor If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: https://github.com/SandroWissmann/System-Monitor
 */
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

            runningProcessesCount: sysinfo.runningProcesses
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
