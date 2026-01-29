import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    width: 684
    height: 350
    minimumWidth: 684
    minimumHeight: 350
    maximumWidth: 684
    maximumHeight: 350
    title: "IPS UIP"

    property string downloadPath: Qt.homePath + "/Downloads"
    // property var selectedCountries: []
    // property var selectedMainlands: []

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        // Countries Section
        Label {
            text: "Countries"
            font.bold: true
        }

        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: countriesField
                text: root.selectedCountries.join(" ")
                Layout.fillWidth: true
                readOnly: true
                placeholderText: "No countries selected"
            }
            Button {
                text: "Choose countries"
                onClicked: countriesDialog.open()
            }
        }

        // Mainlands Section
        Label {
            text: "Mainlands"
            font.bold: true
        }

        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: mainlandsField
                text: root.selectedMainlands.join(" ")
                Layout.fillWidth: true
                readOnly: true
                placeholderText: "No mainlands selected"
            }
            Button {
                text: "Choose mainland"
                onClicked: mainlandsDialog.open()
            }
        }

        // Download Path Section
        Label {
            text: "Download path"
            font.bold: true
        }

        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: pathField
                text: root.downloadPath
                Layout.fillWidth: true
            }
            Button {
                text: "..."
                onClicked: {
                    const newPath = Qt.dialogs.fileDialog.selectExistingDirectory(pathField.text)
                    if (newPath) pathField.text = newPath
                }
            }
        }

        // Spacer
        Item {
            Layout.fillHeight: true
        }

        // Download Button
        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
            Button {
                text: "Download"
                onClicked: {
                    // TODO: Implement download logic
                    console.log("Download path:", pathField.text)
                    console.log("Selected countries:", root.selectedCountries)
                    console.log("Selected mainlands:", root.selectedMainlands)
                }
            }
        }

        // Progress Bar
        ProgressBar {
            id: progressBar
            Layout.fillWidth: true
            value: 0
        }
    }

    // Countries Dialog
    // CountriesDialog {
    //     id: countriesDialog
    //     onAccepted: {
    //         root.selectedCountries = selectedCountries
    //     }
    // }

    // Mainlands Dialog
    // MainlandsDialog {
    //     id: mainlandsDialog
    //     onAccepted: {
    //         root.selectedMainlands = selectedMainlands
    //     }
    // }
}
