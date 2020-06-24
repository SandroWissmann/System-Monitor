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
