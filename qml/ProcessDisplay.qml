import QtQuick 2.15
import QtQuick.Controls 2.15
import com.sysmon 1.0

Item {
    id: root

    TableView {
        id: tableView

        columnWidthProvider: function (column) {
            if(column === 5){
                return tableView.width
            }
            return 100;
        }

        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds

        topMargin: columnsHeader.implicitHeight

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

        Row {
            id: columnsHeader
            y: tableView.contentY
            z: 2
            Repeater {
                model: tableView.columns
                Label {
                    width: tableView.columnWidthProvider(modelData)
                    height: 20
                    text: processTableModel.headerData(modelData, Qt.Horizontal)
                    color: "green"
                    verticalAlignment: Text.AlignVCenter

                    background: Rectangle { color: "#FFFFFF" }
                }
            }
        }
    }
}
