
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
import QtQuick.Controls 2.15
import com.sysmon 1.0

import "header_model"

Item {
    id: root

    HorizontalHeaderView {
        id: horizontalHeaderView
        syncView: tableView
        anchors.left: tableView.left

        model: HeaderModel {}
    }
    TableView {
        id: tableView

        width: parent.width
        height: parent.height - horizontalHeaderView.height
        anchors.top: horizontalHeaderView.bottom
        boundsBehavior: Flickable.StopAtBounds

        columnWidthProvider: function (column) {
            if (column === 5) {
                return tableView.width
            }
            return 100
        }

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
    }
}
