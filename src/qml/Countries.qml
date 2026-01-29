import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 6.0

Rectangle {
    id: countriesDialog
    width: 600
    height: 400
    color: "white"
    property var selectedCountries: []

    signal countriesSelected(var countries)

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        // Scrollable area for countries
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            GridLayout {
                id: countriesGrid
                columns: 3
                rowSpacing: 10
                columnSpacing: 20

                // Countries will be added dynamically from C++
                function addCheckBox(name, checked) {
                    var component = Qt.createComponent("CheckBox.qml");
                    if (component.status === Component.Ready) {
                        var checkbox = component.createObject(countriesGrid, {
                            "text": name,
                            "checked": checked
                        });

                        checkbox.clicked.connect(function() {
                            if (checkbox.checked) {
                                selectedCountries.push(name);
                            } else {
                                selectedCountries.splice(selectedCountries.indexOf(name), 1);
                            }
                        });
                    }
                }
            }
        }

        // Buttons
        RowLayout {
            Layout.alignment: Qt.AlignRight

            Button {
                text: "Cancel"
                onClicked: countriesDialog.close()
            }

            Button {
                text: "OK"
                onClicked: {
                    countriesSelected(selectedCountries)
                    countriesDialog.close()
                }
            }
        }
    }
}
