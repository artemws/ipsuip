import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 6.0

Rectangle {
    id: mainlandDialog
    width: 400
    height: 300
    color: "white"
    property var selectedMainlands: []
    
    signal mainlandsSelected(var mainlands)
    
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        
        // Scrollable area for mainlands
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            
            GridLayout {
                id: mainlandsGrid
                columns: 2
                rowSpacing: 10
                columnSpacing: 20
                
                // Mainlands will be added dynamically from C++
            }
        }
        
        // Buttons
        RowLayout {
            Layout.alignment: Qt.AlignRight
            
            Button {
                text: "Cancel"
                onClicked: mainlandDialog.close()
            }
            
            Button {
                text: "OK"
                onClicked: {
                    mainlandsSelected(selectedMainlands)
                    mainlandDialog.close()
                }
            }
        }
    }
}