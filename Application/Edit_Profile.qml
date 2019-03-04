import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.12
//import Felgo 3.0

Page {
    id:wind
//    height: Screen.height
//        width: Screen.width
function backPressed(){ bbbb.start()}

    MouseArea {
        anchors.fill: parent
        onClicked:  {Qt.inputMethod.hide()}

        PropertyAnimation{
            id:aaaa
            property: "y"
            target: rec
            to:0
            duration: 200
        }
        PropertyAnimation{
            id:bbbb
            property: "y"
            target: rec
            to: 0
            duration: 200
        }
        PropertyAnimation{
            id:dddd
            property: "y"
            target: rec
            to: -roundButton.y
            duration: 200
        }
        PropertyAnimation{
            id:ffff
            property: "y"
            target: rec
            to: -roundButton.y-save_changes.height
            duration: 200
        }
        Rectangle{
            id:root
            height: parent.height
            width: parent.width
            gradient: Gradient{
                GradientStop { position: 0.0;color:"dimgrey"}
                GradientStop { position: 0.25;color:"gray"}
                GradientStop { position: 0.5;color:"darkgrey"}
                GradientStop { position: 0.75;color:"silver"}
                GradientStop{ position: 1.0;color:"lightgrey"}
            }

            Rectangle{
                id: rec
                x: 0
                y: 0
                width: parent.width
                height: parent.height
                color: "transparent"

                MouseArea{
                    x:0
                    y:0
                    id:mouse
                    width: parent.width
                    height: parent.height
                    onPressed:{
                        aaaa.start()
                        Qt.inputMethod.hide()
                    }
                    Rectangle{
                        id: rec1
                        visible: true
                        width: Screen.width
                        height: (Screen.height)/4
                        color: "transparent"

                        Rectangle{
                            x: 0
                            id:small
                            visible: true
                            width: Screen.width
                            height: (Screen.height)/12
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
                                onClicked: stack00.pop()
                            }
                            Text {
                                id: f_pass
                                text: qsTr("Edit profile")
                                color: "white"
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                // anchors.bottom: roundButton.top
                                font.pointSize: 30
                            }
                        }

                        RoundButton {
                            id: roundButton
                            width: 70
                            height: 70
//                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: small.bottom
                            anchors.topMargin: 10
                            text: "+"
                        }

                        Button {
                            id: changePhoto
                            background: Rectangle{
                                color: "transparent"
                            }
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: roundButton.bottom
                            anchors.topMargin: 10
                            Text {
                                text: qsTr("Change photo")
                                color: "white"
                                anchors.centerIn: parent
                            }
                            font.pointSize: 11
                        }
                    }

                    Rectangle{
                        id:rec2
                        x:0

                        visible: true
                        width: Screen.width
                        height: (parent.height - rec1.height)
                        anchors.bottom: parent.bottom

                        color: "transparent"
                        Column {
                            id: column

                            width: parent.width
                            height: parent.height/2
                            anchors.top: parent.top

                            spacing: height/6
                            TextField{
                                id:edit_name

                                width: parent.width
                                height: parent.height/6
                                color: "white"
                                text: qsTr("Name")
                                font.pointSize: 11
                                background: Rectangle{
                                    color: "transparent"
                                }
                                Rectangle {
                                    id:name_rect
                                    color: "white"
                                    height: 1
                                    width: parent.width
                                    anchors.bottom: parent.bottom
                                }
                                onEditingFinished:  { name_rect.height = 1; name_rect.color = "white"}
                                onPressed:   { name_rect.height = 2 ; name_rect.color = "teal"; bbbb.start()}
                            }

                            TextField{
                                id:edit_surname
                                width: parent.width
                               height: parent.height/6
                                color: "white"
                                text: qsTr("Surname")
                                font.pointSize: 11
                                background: Rectangle{
                                    color: "transparent"
                                }
                                Rectangle {
                                    id:surname_rect
                                    color: "white"
                                    height: 1
                                    width: parent.width
                                    anchors.bottom: parent.bottom
                                }
                                onEditingFinished:  { surname_rect.height = 1; surname_rect.color = "white"}
                                onPressed:   { surname_rect.height = 2 ; surname_rect.color = "teal";dddd.start()}
                            }

                            TextField{
                                id:edit_nickname
                                width: parent.width
                                height: parent.height/6
                                color: "white"
                                text: qsTr("Nickname")
                                font.pointSize: 11
                                background: Rectangle{
                                    color: "transparent"
                                }
                                Rectangle {
                                    id:nick_rect
                                    color: "white"
                                    height: 1
                                    width: parent.width
                                    anchors.bottom: parent.bottom
                                }
                                onEditingFinished:  { nick_rect.height = 1; nick_rect.color = "white"}
                                onPressed:   { nick_rect.height = 2 ; nick_rect.color = "teal";ffff.start()}
                            }
                        }
Rectangle{
    width: parent.width
    height: parent.height-column.height-44
    anchors.top: column.bottom
    color: "transparent"
                        Button{
                            id:save_changes
                            background: Rectangle{
                                radius: 30
                                color: "teal"
                                Text {
                                    text: qsTr("Save changes")
                                    color: "white"
                                    anchors.centerIn: parent
                                    font.pointSize: 11
                                }
                            }
                            opacity: enabled ? 1: 0.5
                            //anchors.horizontalCenter: parent.horizontalCenter
//                            anchors.top:column.bottom
//                            anchors.topMargin: 50
                            //anchors.top: parent.top
                            //anchors.topMargin: 15
                            anchors.centerIn: parent
                            width: 130
                            height: 30
                            font.weight: Font.Light
                            font.pointSize: 10
                            font.family: "Courier"
                            font.capitalization: Font.Capitalize
                            //spacing: 5
                            enabled: (edit_name.text === "" || edit_surname.text === "" || edit_nickname.text === "" )?false:true
                            onPressed: {aaaa.start()}
                            onClicked: stack00.pop()
                        }
}
                    }
                }
            }
        }
    }
}








/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
