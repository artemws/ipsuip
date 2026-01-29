import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: root
    title: "Select Mainlands"
    width: 600
    height: 400
    modality: Qt.ApplicationModal
    standardButtons: Dialog.Ok | Dialog.Cancel

    property var selectedMainlands: []
    property var mainlandsModel: []

    ColumnLayout {
        anchors.fill: parent

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            GridLayout {
                id: mainlandsGrid
                columns: 6
                rowSpacing: 10
                columnSpacing: 10

                Repeater {
                    model: root.mainlandsModel
                    CheckBox {
                        text: modelData.name
                        checked: modelData.checked
                        onClicked: modelData.checked = checked
                    }
                }
            }
        }
    }

    onAccepted: {
        selectedMainlands = []
        for (var i = 0; i < mainlandsGrid.children.length; i++) {
            var checkbox = mainlandsGrid.children[i]
            if (checkbox.checked) {
                selectedMainlands.push(checkbox.text)
            }
        }
    }
}
