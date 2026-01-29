// qml_prototype/components/Mainland.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GroupBox {
    title: "Mainland"
    Layout.fillWidth: true
    Layout.fillHeight: true

    ScrollView {
        anchors.fill: parent

        GridLayout {
            columns: 3
            rowSpacing: 10
            columnSpacing: 10
            width: parent.width

            Repeater {
                model: [
                    "Afghanistan", "Albania", "Algeria", "Andorra", "Angola",
                    "Antigua and Barbuda", "Argentina", "Armenia", "Australia", "Austria",
                    "Azerbaijan", "Bahamas", "Bahrain", "Bangladesh", "Barbados"
                ]
                CheckBox {
                    text: modelData
                    checked: false
                }
            }
        }
    }
}