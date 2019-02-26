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
                event.accepted = true;
               // if (stack.depth >= 1) {
                    stack.pop();
               // } else { Qt.quit(); }
            }
        }
        focus: true
        anchors.fill: parent
        id:stack
        initialItem: Qt.resolvedUrl("Sign_in.qml")
    }
}
