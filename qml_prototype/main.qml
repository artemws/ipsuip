// qml_prototype/main.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import IpsuipPrototype

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Ipsuip QML Prototype"

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem { text: "Exit"; onTriggered: Qt.quit() }
        }
    }

    StackView {
        id: stackView
        initialItem: mainPage
        anchors.fill: parent
    }

    component MainPage: Page {
        ColumnLayout {
            anchors.fill: parent
            spacing: 10
            padding: 10

            Countries {
                Layout.fillWidth: true
            }

            Mainland {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}