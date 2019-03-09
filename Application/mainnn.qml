import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtSensors 5.12
ApplicationWindow {
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("MafClub")
    StackView{
        Keys.onPressed:  {
            if (event.key === Qt.Key_Back) {
                event.accepted = true
                var topStack = stack55.top()
                if (stack55.depth > 1) {
                    if(topStack instanceof Edit_Profile === true){console.log("aaaaaaaaaaaaaaa")}
                    stack55.pop()
                } else { Qt.quit() }
            }
        }
        focus: true
        anchors.fill: parent
        id:stack55
        initialItem: Qt.resolvedUrl("Home.qml")
    }
}
