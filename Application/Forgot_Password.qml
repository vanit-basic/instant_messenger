import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.12

Page {
    id:wind   
    Rectangle{
        width: Screen.width
        height: Screen.height
        gradient: Gradient{
            GradientStop { position: 0.0;color:"dimgrey"}
            GradientStop { position: 0.25;color:"gray"}
            GradientStop { position: 0.5;color:"darkgrey"}
            GradientStop { position: 0.75;color:"silver"}
            GradientStop{ position: 1.0;color:"lightgrey"}
        }
        MouseArea{
            anchors.fill:parent
            onPressed:{Qt.inputMethod.hide()}
            Rectangle{
                x:0
                id: rec1
                visible: true
                width: Screen.width
                height: (Screen.height)/12
                color: "transparent"
                Button{
                    id:back
                    x: 0
                    y:0
                    width:parent.height
                    height: parent.height
                    background: Rectangle{
                        color: "transparent"
                    }
                    onPressed: stack.pop()
                    Text {
                        id: back_text
                        anchors.fill:parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: qsTr("<")
                        font.pointSize: 30
                        color: "white"
                    }
                }
                Text {
                    id: f_pass
                    text: qsTr("Reset Password")
                    color: "#000000"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 30
                }
            }
            Rectangle{
                id:rec2
                y:rec1.height
                visible: true
                width: Screen.width
                height: Screen.height-rec1.height
                color: "transparent"
                anchors.top: rec1.bottom
                TextField{
                    id:email
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 40
                    width: parent.width
                    height: 50
                    color: "white"
                    background: Rectangle{
                        color: "transparent"
                    }
                    placeholderText: "Email"
                    Rectangle {
                        id:email_rect
                        color: "white"
                        height: 1
                        width: parent.width
                        anchors.bottom: parent.bottom
                    }
                    onEditingFinished:  {email_rect.height = 1; email_rect.color = "white"}
                    onPressed:   { email_rect.height = 2 ; email_rect.color = "#325f5f"}
                }
                Button{
                    id:reset
                    height: 30
                    width: 120
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: email.bottom
                    anchors.topMargin: 15
                    background: Rectangle{
                        radius: 30
                        color: "teal"
                    }
                    text: "Reset"
                    enabled: (email.text ==="")?false:true
                    onPressed: {
                        code.visible = true
                        ok.visible = true
                        reset.visible = false
                        email.visible = false
                    }
                }
                TextField{
                    id:code
                    visible: false
                    height:50
                    width: 150
                    anchors.top: reset.bottom
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignLeft
                    placeholderText: "Code"
                    background: Rectangle{
                        color: "white"
                        height: 1
                        width: parent.width
                        anchors.bottom: parent.bottom
                    }

                    Rectangle {
                        id:code_rect
                        color: "white"
                        height: 1
                        width: parent.width
                        anchors.bottom: parent.bottom
                    }
                    onEditingFinished:  {code_rect.height = 1; code_rect.color = "white"}
                    onPressed:   { code_rect.height = 2 ; code_rect.color = "#325f5f"}
                }
                Button{
                    id:ok
                    visible: false
                    height: 30
                    width: 120
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: code.bottom
                    anchors.topMargin:15
                    background: Rectangle{
                        radius: 30
                        color: "teal"
                    }
                    text: "Ok"
                    enabled: (code.text ==="")?false:true
                    onPressed: {
                        code.visible = false
                        ok.visible = false
                        rec3.visible =true
                    }
                }
                Rectangle{
                    id:rec3
                    x:0
                    visible: false
                    width: Screen.width
                    height: Screen.height/2
                    color: "transparent"
                    anchors.top: parent.top
                    anchors.topMargin: parent.height/12
                    MouseArea{
                        id:mouse1
                        anchors.fill: parent
                        onPressed:{Qt.inputMethod.hide()}
                        TextField{
                            id:newp
                            width: parent.width
                            height: 50
                            color: "white"
                            anchors.top: parent.top
                            anchors.topMargin: 50
                            echoMode: TextField.Password
                            passwordCharacter: "*"
                            placeholderText: "New Password"
                            background: Rectangle{
                                color: "transparent"
                            }
                            Button{
                            id:see_pass
                            width: parent.height+20
                            height: parent.height
                            background: Rectangle{
                            color: "transparent"
                            }
                            anchors.bottom: parent.bottom
                            anchors.right: parent.right
                            icon.source: "qrc:/glaz1.png"
                            icon.color: "white"

                            onClicked: {
                            newp.echoMode === TextInput.Password?(newp.echoMode =TextInput.Normal ) :(newp.echoMode = TextInput.Password)
                            icon.source == "qrc:/glaz1.png"? icon.source= "qrc:/glaz.png": icon.source= "qrc:/glaz1.png"

                            }



                            }
                            Rectangle {
                                id:new_rect
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onEditingFinished:  {new_rect.height = 1; new_rect.color = "white"}
                            onPressed:   {new_rect.height = 2 ; new_rect.color = "#325f5f"}
                        }
                        TextField{
                            id:repeatp
                            width: parent.width
                            height: 50
                            color: "white"
                            anchors.top: newp.bottom
                            anchors.topMargin: 50
                            echoMode: TextField.Password
                            passwordCharacter: "*"
                            background: Rectangle{
                                color: "transparent"
                            }
                            Button{
                            id:see_pass1
                            width: parent.height+20
                            height: parent.height
                            background: Rectangle{
                            color: "transparent"
                            }
                            anchors.bottom: parent.bottom
                            anchors.right: parent.right
                            icon.source: "qrc:/glaz1.png"
                            icon.color: "white"

                            onClicked: {
                            repeatp.echoMode === TextInput.Password?(repeatp.echoMode =TextInput.Normal ) :(repeatp.echoMode = TextInput.Password)
                            icon.source == "qrc:/glaz1.png"? icon.source= "qrc:/glaz.png": icon.source= "qrc:/glaz1.png"

                            }



                            }
                            placeholderText: "Repeat Password"

                            Rectangle {
                                id:repeat_rect
                                color: "white"
                                height: 1
                                width: parent.width
                                anchors.bottom: parent.bottom
                            }
                            onEditingFinished:  {repeat_rect.height = 1; repeat_rect.color = "white"}
                            onPressed:   {repeat_rect.height = 2 ; repeat_rect.color = "#325f5f"}
                        }
                        Button{
                            id:submit
                            height: 30
                            width: 120
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: repeatp.bottom
                            anchors.topMargin:30
                            background: Rectangle{
                                radius: 30
                                color: "teal"
                            }
                            text: "Submit"
                            enabled: (newp.text ==="" || repeatp.text ==="")?false:true
                        }
                    }
                }
            }
        }
    }
}
