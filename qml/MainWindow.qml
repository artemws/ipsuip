import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: root
    width: 800
    height: 600
    visible: true
    title: "IPS UIP"

    // Свойства для связи с C++ контроллером
    property string downloadPath: mainController.downloadPath
    property var selectedCountries: mainController.selectedCountries
    property var selectedMainlands: mainController.selectedMainlands
    property double progressValue: mainController.progressValue

    // Сигналы для обработки событий
    signal countriesSelected(var countries)
    signal mainlandsSelected(var mainlands)
    signal downloadStarted()
    signal downloadCompleted()
    signal errorOccurred(string message)

    // Обработчики сигналов от контроллера
    onDownloadPathChanged: {
        console.log("Download path changed:", downloadPath)
    }

    onSelectedCountriesChanged: {
        console.log("Selected countries changed:", selectedCountries)
    }

    onSelectedMainlandsChanged: {
        console.log("Selected mainlands changed:", selectedMainlands)
    }

    onProgressValueChanged: {
        progressBar.value = progressValue
    }

    Connections {
        target: mainController
        function onDownloadStarted() {
            downloadStarted()
            downloadDialog.open()
        }
        function onDownloadCompleted() {
            downloadCompleted()
            downloadDialog.close()
        }
        function onErrorOccurred(message) {
            errorOccurred(message)
            errorDialog.text = message
            errorDialog.open()
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        // Заголовок
        Label {
            text: "IPS UIP - Parser"
            font.pixelSize: 24
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }

        // Разделитель
        Rectangle {
            height: 2
            color: "#cccccc"
            Layout.fillWidth: true
        }

        // Страны
        ColumnLayout {
            Layout.fillWidth: true
            
            Label {
                text: "Страны"
                font.bold: true
                font.pixelSize: 16
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                TextField {
                    id: countriesField
                    Layout.fillWidth: true
                    readOnly: true
                    placeholderText: "Выберите страны..."
                    text: selectedCountries.join(", ")
                }

                Button {
                    text: "Выбрать страны"
                    onClicked: countriesDialog.open()
                }
            }
        }

        // Материки
        ColumnLayout {
            Layout.fillWidth: true
            
            Label {
                text: "Материки"
                font.bold: true
                font.pixelSize: 16
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                TextField {
                    id: mainlandsField
                    Layout.fillWidth: true
                    readOnly: true
                    placeholderText: "Выберите материки..."
                    text: selectedMainlands.join(", ")
                }

                Button {
                    text: "Выбрать материки"
                    onClicked: mainlandsDialog.open()
                }
            }
        }

        // Путь загрузки
        ColumnLayout {
            Layout.fillWidth: true
            
            Label {
                text: "Путь для загрузки"
                font.bold: true
                font.pixelSize: 16
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                TextField {
                    id: pathField
                    Layout.fillWidth: true
                    text: downloadPath
                    onTextChanged: mainController.downloadPath = text
                }

                Button {
                    text: "Обзор..."
                    onClicked: mainController.selectDirectory()
                }
            }
        }

        // Прогресс бар
        ColumnLayout {
            Layout.fillWidth: true
            
            Label {
                text: "Прогресс"
                font.bold: true
                font.pixelSize: 16
            }

            ProgressBar {
                id: progressBar
                Layout.fillWidth: true
                value: 0
            }
        }

        // Кнопка скачивания
        Button {
            text: "Начать скачивание"
            Layout.alignment: Qt.AlignRight
            Layout.fillWidth: true
            font.pixelSize: 16
            font.bold: true
            onClicked: mainController.startDownload()
        }
    }

    // Диалог выбора стран
    CountriesDialog {
        id: countriesDialog
        onAccepted: {
            mainController.updateSelectedCountries(selectedCountries)
        }
    }

    // Диалог выбора материков
    MainlandsDialog {
        id: mainlandsDialog
        onAccepted: {
            mainController.updateSelectedMainlands(selectedMainlands)
        }
    }

    // Диалог прогресса
    Dialog {
        id: downloadDialog
        title: "Загрузка..."
        modal: true
        closePolicy: Dialog.NoButton
        
        ColumnLayout {
            anchors.fill: parent
            spacing: 10
            
            ProgressBar {
                Layout.fillWidth: true
                value: progressValue
            }
            
            Label {
                text: "Пожалуйста, подождите..."
            }
        }
    }

    // Диалог ошибок
    Dialog {
        id: errorDialog
        title: "Ошибка"
        modal: true
        standardButtons: Dialog.Ok
        
        ColumnLayout {
            anchors.fill: parent
            spacing: 10
            
            Label {
                id: errorLabel
                text: errorDialog.text
                wrapMode: Text.WordWrap
            }
        }
    }
}