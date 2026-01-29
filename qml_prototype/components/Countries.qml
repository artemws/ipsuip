// qml_prototype/components/Countries.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GroupBox {
    title: "Countries"
    Layout.fillWidth: true

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        padding: 10

        CheckBox {
            text: "Select All"
            checked: false
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ColumnLayout {
                spacing: 5
                width: parent.width

                Repeater {
                    model: ["Africa", "America", "Asia", "Europe", "Oceania"]
                    CheckBox {
                        text: modelData
                        checked: false
                    }
                }
            }
        }
    }
}