// qml_prototype/components/styles/Theme.qml
import QtQuick.Controls

QtObject {
    id: theme

    // Colors
    property color primaryColor: "#3574F0"
    property color secondaryColor: "#2E3440"
    property color backgroundColor: "#FFFFFF"
    property color textColor: "#2E3440"
    property color accentColor: "#4CAF50"

    // Fonts
    property string fontFamily: "Noto Sans"
    property int fontSizeSmall: 12
    property int fontSizeMedium: 14
    property int fontSizeLarge: 16

    // Spacing
    property int spacingSmall: 5
    property int spacingMedium: 10
    property int spacingLarge: 20

    // Apply theme to Qt Quick Controls
    Component.onCompleted: {
        Qt.styleHints.accentColor = accentColor
        ApplicationWindow {
            color: backgroundColor
        }
    }
}