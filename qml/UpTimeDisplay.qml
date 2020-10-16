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

Item {
    id: root

    required property int upTimeInSeconds
    property alias fontSize: text.font.pointSize

    Text{
        id: text

        text: qsTr("Up Time: " + elapsedTimeAsString(parent.upTimeInSeconds));
    }

    function elapsedTimeAsString(seconds)
        // format hh:mm::ss
    {
        var minutes = seconds / 60;
        minutes = Math.floor(minutes);
        seconds -= minutes * 60;
        seconds = Math.floor(seconds);

        var hours = minutes / 60;
        hours = Math.floor(hours);
        minutes -= hours * 60;
        minutes = Math.floor(minutes)

        if (hours > 99) {
            hours = 99;
        }

        return fillWithNLeadingSigns(hours.toString(), 2, '0') + ":" +
                fillWithNLeadingSigns(minutes.toString(), 2, '0') + ":" +
                fillWithNLeadingSigns(seconds.toString(), 2, '0');
    }

    function fillWithNLeadingSigns(str, minSize, sign)
    {
        var fillsCount = minSize;
        fillsCount -= str.length;
        if(fillsCount > 0) {
            var fill = "";
            for(var i = 0; i< fillsCount; ++i) {
                fill +=sign;
            }
            return fill.concat(str);
        }
        return str;
    }
}
