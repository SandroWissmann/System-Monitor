import QtQuick 2.15
import QtQuick.Controls 2.15
import com.sysmon 1.0

Item {
    TableView {
        id: tableView

        columnWidthProvider: function (column) { return 100; }

        anchors.fill: parent

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
                model: tableView.columns > 0 ? tableView.columns : 1
                Label {
                    width: tableView.columnWidthProvider(modelData)
                    height: 35
                    text: processTableModel.headerData(modelData, Qt.Horizontal)
                    color: "green"
                    verticalAlignment: Text.AlignVCenter

                    background: Rectangle { color: "#FFFFFF" }
                }
            }
        }

        ScrollIndicator.horizontal: ScrollIndicator { }
    }
}
