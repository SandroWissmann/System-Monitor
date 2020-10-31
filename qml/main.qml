
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
import QtQuick.Window 2.15
import com.sysmon 1.0

import "system_information_display"
import "process_display"

Window {
    id: root

    visible: true
    width: 840
    height: 480
    title: qsTr("System Monitor")

    SystemInformationDisplay {
        id: systemInformationDisplay

        width: root.width
    }

    ProcessDisplay {
        anchors.top: systemInformationDisplay.bottom

        id: processDisplay

        width: root.width
        height: root.height - systemInformationDisplay.height
    }
}
