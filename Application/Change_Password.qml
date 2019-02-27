import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Page {
    id:wind
    //    visible: true
    //    width: Screen.width
    //    height: Screen.height

    Rectangle{
        id:rec
        anchors.fill: parent
        //visible: true
//        width: Screen.width
//        height: Screen.height
        color: "light blue"

        Rectangle{
            x: 0
            id: small
            visible: true
            width: parent.width
            height: (parent.height)/12
            color: "transparent"
            Button{
                id:back
                x: 0
                y: 0
                width:parent.height
                height: parent.height
                background: Rectangle{
                    color: "transparent"
                }
                Text {
                    id: back_text
                    anchors.fill:parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("<")
                    font.pointSize: 30
                    color: "white"
                }
                onClicked:stack.pop()
            }
            Text {
                id: f_pass
                text: qsTr("Change Password")
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 30
            }
        }

        Column {
            id: column
            x: rec.x+50
            y:   small.height + 15
            width: rec.width - 100
            spacing: 20
            TextField{
                id:currentp
                x:0
                y:0
                width: parent.width
                height: 50
                color: "white"
                background: Rectangle{
                    color: "transparent"
                }
                placeholderText: "Current Password"
                Rectangle {
                    id:current
                    color: "white"
                    height: 1
                    width: parent.width
                    anchors.bottom: parent.bottom
                }
            }
            TextField{
                id:newp
                width: parent.width
                height: 50
                color: "white"
                placeholderText: "New Password"
                background: Rectangle{
                    color: "transparent"
                }
                Rectangle {
                    id:neww
                    color: "white"
                    height: 1
                    width: parent.width
                    anchors.bottom: parent.bottom
                }
            }
            TextField{
                id:confirmp
                width: parent.width
                height: 50
                color: "white"
                placeholderText: "Confirm Password"
                background: Rectangle{
                    color: "transparent"
                }
                Rectangle {
                    id:confirm
                    color: "white"
                    height: 1
                    width: parent.width
                    anchors.bottom: parent.bottom
                }
            }
        }
        Button{
            id:save_changes
            background: Rectangle{
                radius: 30
                color: "teal"
            }
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: rec.bottom
            anchors.bottomMargin: 100
            width: 180
            text: "Save changes"
            enabled: (currentp.text === "" || newp.text === "" || confirmp.text === "" )?false:true
            onClicked: stack.pop()
        }

    }
}



/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
