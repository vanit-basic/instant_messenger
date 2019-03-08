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

//        PropertyAnimation{
//            id:aaaa
//            property: "y"
//            target: rec
//            to:0
//            duration: 200
//        }
//        PropertyAnimation{
//            id:bbbb
//            property: "y"
//            target: rec
//            to: 0
//            duration: 200
//        }
//        PropertyAnimation{
//            id:dddd
//            property: "y"
//            target: rec
//            to: -roundButton.y
//            duration: 200
//        }
//        PropertyAnimation{
//            id:ffff
//            property: "y"
//            target: rec
//            to: -roundButton.y-save_changes.height
//            duration: 200
//        }
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

//            Rectangle{
//                id: rec
//                x: 0
//                y: 0
//                width: parent.width
//                height: parent.height
//                color: "transparent"

                MouseArea{
                    x:0
                    y:0
                    id:mouse
                    width: parent.width
                    height: parent.height
                    onPressed:{

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
                            onClicked: console.log(edit_name.height,"+",edit_surname.height,"+",edit_nickname.height)
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
                        height: (parent.height - rec1.height-50)
                        anchors.bottom: parent.bottom
                        anchors.topMargin: 50

                        color: "transparent"
                        Column {
                            id: column
                            x:25
                            width: parent.width-50
                            height: parent.height/2
                            anchors.top: parent.top

                            spacing: height/6
                            Row{

                                width: parent.width
                                height: parent.height/6
                                Rectangle{
                                    id:rec_name
                                    width: parent.width/3
                                    height: parent.height
                                color: "transparent"
                                Text {
                                    id: name_text
                                    text: qsTr("Name")
                                    anchors.bottom: parent.bottom
                                }

                                }

                            TextInput{
                                id:edit_name

                                width: parent.width-rec_name.width
                                height: parent.height
                                color: "white"


                                Rectangle {
                                    id:name_rect
                                    color: "white"
                                    height: 1
                                    width: parent.width
                                    anchors.bottom: parent.bottom
                                }

                                EnterKey.type:  Qt.EnterKeyNext
                                onEditingFinished:  { edit_surname.focus = true}

                            }
                            }
                            Row{

                                width: parent.width
                                height: parent.height/6
                                Rectangle{
                                    id:rec_surname
                                    width: parent.width/3
                                    height: parent.height
                                color: "transparent"
                                Text {
                                    id: surname_text
                                    text: qsTr("Surname")
                                    anchors.bottom: parent.bottom
                                }

                                }

                            TextInput{
                                id:edit_surname
                                width: parent.width-rec_surname.width
                               height: parent.height
                                color: "white"

                                Rectangle {
                                    id:surname_rect
                                    color: "white"
                                    height: 1
                                    width: parent.width
                                    anchors.bottom: parent.bottom
                                }
                                onEditingFinished:  { edit_nickname.focus = true}
                                EnterKey.type:  Qt.EnterKeyNext
                            }
                            }
                            Row{

                                width: parent.width
                                height: parent.height/6
                                Rectangle{
                                    id:rec_nickname
                                    width: parent.width/3
                                    height: parent.height
                                color: "transparent"
                                Text {
                                    id: nickname_text
                                    text: qsTr("Nickname")
                                    anchors.bottom: parent.bottom
                                }

                                }


                            TextInput{
                                id:edit_nickname
                                width: parent.width-rec_nickname.width
                                height: parent.height
                                color: "white"

                                Rectangle {
                                    id:nick_rect
                                    color: "white"
                                    height: 1
                                    width: parent.width
                                    anchors.bottom: parent.bottom
                                }
                                onEditingFinished:  { nick_rect.height = 1; nick_rect.color = "white"}
                                //EnterKey.type:  Qt.EnterKeyNext
                            }
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

                            anchors.centerIn: parent
                            width: 130
                            height: 30
                            font.weight: Font.Light
                            font.pointSize: 10
                            font.family: "Courier"
                            font.capitalization: Font.Capitalize
                            //spacing: 5
                            enabled: (edit_name.text === "" || edit_surname.text === "" || edit_nickname.text === "" )?false:true

                            onClicked: stack00.pop()
                        }
}
                    }
              //  }
            }
        }
    }
}








/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
