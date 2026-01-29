import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

Dialog {
    id: root
    title: "Выберите материки"
    modal: true
    width: 500
    height: 400
    standardButtons: Dialog.Ok | Dialog.Cancel

    property var selectedMainlands: []

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        // Информация
        Label {
            text: "Выберите материки для обработки:"
            font.bold: true
        }

        // Список материков
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: mainlandsList
                model: mainlandsModel
                delegate: mainlandDelegate
                clip: true
                spacing: 5

                // Модель материков
                ListModel {
                    id: mainlandsModel
                    
                    Component.onCompleted: {
                        // Загружаем данные из C++
                        loadMainlands()
                    }
                    
                    function loadMainlands() {
                        // Здесь можно загрузить реальные данные из C++
                        // Временно добавим тестовые данные
                        append({"name": "Europe", "code": "EU"})
                        append({"name": "Asia", "code": "AS"})
                        append({"name": "Africa", "code": "AF"})
                        append({"name": "North America", "code": "NA"})
                        append({"name": "South America", "code": "SA"})
                        append({"name": "Oceania", "code": "OC"})
                        append({"name": "Antarctica", "code": "AN"})
                        append({"name": "Unknown", "code": "ZZ"})
                    }
                }

                // Делегат для элемента списка
                Component {
                    id: mainlandDelegate
                    
                    Rectangle {
                        width: ListView.view.width
                        height: 50
                        color: checked ? "#e8f5e8" : "transparent"
                        border.color: "#cccccc"
                        border.width: 1

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 15
                            spacing: 15

                            CheckBox {
                                id: mainlandCheckbox
                                checked: selectedMainlands.indexOf(model.name) !== -1
                                onCheckedChanged: {
                                    if (checked) {
                                        if (selectedMainlands.indexOf(model.name) === -1) {
                                            selectedMainlands.push(model.name)
                                        }
                                    } else {
                                        var index = selectedMainlands.indexOf(model.name)
                                        if (index !== -1) {
                                            selectedMainlands.splice(index, 1)
                                        }
                                    }
                                }
                            }

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 5

                                Label {
                                    text: model.name
                                    font.bold: true
                                }

                                Label {
                                    text: model.code
                                    color: "#666666"
                                    font.pixelSize: 12
                                }
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
                text: "Выбрано: " + selectedMainlands.length + " материков"
                color: "#666666"
            }
            
            Button {
                text: "Очистить все"
                onClicked: {
                    selectedMainlands = []
                }
            }
            
            Button {
                text: "Выбрать все"
                onClicked: {
                    selectedMainlands = []
                    for (var i = 0; i < mainlandsModel.count; i++) {
                        selectedMainlands.push(mainlandsModel.get(i).name)
                    }
                }
            }
        }
    }

    onAccepted: {
        // Сигнал о том, что выбор завершен
        selectedMainlands = selectedMainlands
    }

    onRejected: {
        selectedMainlands = []
    }
}