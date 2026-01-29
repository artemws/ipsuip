import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

Dialog {
    id: root
    title: "Выберите страны"
    modal: true
    width: 600
    height: 500
    standardButtons: Dialog.Ok | Dialog.Cancel

    property var selectedCountries: []

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        // Поиск
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            TextField {
                id: searchField
                Layout.fillWidth: true
                placeholderText: "Поиск стран..."
                onTextChanged: {
                    // Фильтрация стран при вводе
                    filterModel.filter = searchField.text.toLowerCase()
                }
            }
        }

        // Список стран
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: countriesList
                model: filterModel
                delegate: countryDelegate
                clip: true
                spacing: 5

                // Модель с фильтрацией
                ListModel {
                    id: allCountriesModel
                    
                    // Загружаем данные из C++
                    Component.onCompleted: {
                        loadCountries()
                    }
                    
                    function loadCountries() {
                        // Здесь можно загрузить реальные данные из C++
                        // Временно добавим тестовые данные
                        append({"name": "Russia", "code": "RU"})
                        append({"name": "China", "code": "CN"})
                        append({"name": "USA", "code": "US"})
                        append({"name": "Germany", "code": "DE"})
                        append({"name": "France", "code": "FR"})
                        append({"name": "United Kingdom", "code": "GB"})
                        append({"name": "Japan", "code": "JP"})
                        append({"name": "India", "code": "IN"})
                        append({"name": "Brazil", "code": "BR"})
                        append({"name": "Canada", "code": "CA"})
                        append({"name": "Australia", "code": "AU"})
                        append({"name": "Spain", "code": "ES"})
                        append({"name": "Italy", "code": "IT"})
                        append({"name": "South Korea", "code": "KR"})
                        append({"name": "Mexico", "code": "MX"})
                        append({"name": "Indonesia", "code": "ID"})
                        append({"name": "Netherlands", "code": "NL"})
                        append({"name": "Saudi Arabia", "code": "SA"})
                        append({"name": "Turkey", "code": "TR"})
                        append({"name": "Taiwan", "code": "TW"})
                    }
                }

                // Фильтрация
                ListModel {
                    id: filterModel
                    
                    function filter(text) {
                        clear()
                        for (var i = 0; i < allCountriesModel.count; i++) {
                            var country = allCountriesModel.get(i)
                            if (country.name.toLowerCase().includes(text) || 
                                country.code.toLowerCase().includes(text)) {
                                append(country)
                            }
                        }
                    }
                }

                // Делегат для элемента списка
                Component {
                    id: countryDelegate
                    
                    Rectangle {
                        width: ListView.view.width
                        height: 40
                        color: checked ? "#e3f2fd" : "transparent"
                        border.color: "#cccccc"
                        border.width: 1

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 10
                            spacing: 10

                            CheckBox {
                                id: countryCheckbox
                                checked: selectedCountries.indexOf(model.name) !== -1
                                onCheckedChanged: {
                                    if (checked) {
                                        if (selectedCountries.indexOf(model.name) === -1) {
                                            selectedCountries.push(model.name)
                                        }
                                    } else {
                                        var index = selectedCountries.indexOf(model.name)
                                        if (index !== -1) {
                                            selectedCountries.splice(index, 1)
                                        }
                                    }
                                }
                            }

                            Label {
                                text: model.name
                                Layout.fillWidth: true
                            }

                            Label {
                                text: model.code
                                color: "#666666"
                            }
                        }
                    }
                }
            }
        }

        // Выбрано
        RowLayout {
            Layout.fillWidth: true
            
            Label {
                text: "Выбрано: " + selectedCountries.length + " стран"
                color: "#666666"
            }
            
            Button {
                text: "Очистить все"
                onClicked: {
                    selectedCountries = []
                }
            }
            
            Button {
                text: "Выбрать все"
                onClicked: {
                    selectedCountries = []
                    for (var i = 0; i < allCountriesModel.count; i++) {
                        selectedCountries.push(allCountriesModel.get(i).name)
                    }
                }
            }
        }
    }

    onAccepted: {
        // Сигнал о том, что выбор завершен
        selectedCountries = selectedCountries
    }

    onRejected: {
        selectedCountries = []
    }
}