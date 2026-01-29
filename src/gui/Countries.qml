import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: root
    title: "Select Countries"
    width: 600
    height: 400
    modality: Qt.ApplicationModal
    standardButtons: Dialog.Ok | Dialog.Cancel

    property var selectedCountries: []

    ColumnLayout {
        anchors.fill: parent
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            GridLayout {
                id: countriesGrid
                columns: 10
                rowSpacing: 10
                columnSpacing: 10
                
                // Countries will be added dynamically from C++
            }
        }
    }

    onAccepted: {
        selectedCountries = []
        for (var i = 0; i < countriesGrid.children.length; i++) {
            var checkbox = countriesGrid.children[i]
            if (checkbox.checked) {
                selectedCountries.push(checkbox.text)
            }
        }
    }
}