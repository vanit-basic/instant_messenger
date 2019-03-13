import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.12

Page {
    id:wind

    MouseArea {
        anchors.fill: parent
        onPressed: {Qt.inputMethod.hide()}

        Rectangle{
            id:rec
            anchors.fill: parent

            gradient: Gradient{
                GradientStop { position: 0.0;color:"dimgrey"}
                GradientStop { position: 0.25;color:"gray"}
                GradientStop { position: 0.5;color:"darkgrey"}
                GradientStop { position: 0.75;color:"silver"}
                GradientStop{ position: 1.0;color:"lightgrey"}
            }

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
                    onClicked:stack00.pop()
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
                x: 25
                y:   small.height + 50
                width: parent.width - 50
                spacing: 50
                Row{

                    width: parent.width
                    height: 50
                    Rectangle{
                        id:rec_pass
                        width: confirm_pass_text.width+5
                        height: parent.height
                        color: "transparent"
                        Text {
                            id: pass_text
                            text: qsTr("Current Password")
                            anchors.bottom: parent.bottom
                            color: "white"
                        }

                    }
                    Rectangle{
                        width: parent.width-confirm_pass_text.width
                        height: parent.height
                        color: "transparent"
                        Button{
                        id:see_pass
                        width: parent.height
                        height: parent.height
                        background: Rectangle{
                        color: "transparent"
                        }
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        icon.source: "qrc:/glaz1.png"
                        icon.color: "white"

                        onClicked: {
                        currentp.echoMode === TextInput.Password?(currentp.echoMode =TextInput.Normal ) :(currentp.echoMode = TextInput.Password)
                        icon.source == "qrc:/glaz1.png"? icon.source= "qrc:/glaz.png": icon.source= "qrc:/glaz1.png"
                        }
                        }
                        Rectangle {
                            id:current
                            color: "white"
                            height: 1
                            width: parent.width
                            anchors.bottom: parent.bottom
                        }
                    TextInput{
                        id:currentp
                        width: parent.width-see_pass.width
                        height: 20
                        anchors.bottom: parent.bottom
                        color: "white"
                        clip: true
                        echoMode: TextInput.Password
                        passwordCharacter: "*"
                        EnterKey.type:  Qt.EnterKeyNext
                        onAccepted:  { newp.focus = true}
                    }
                }
                }
                Row{

                    width: parent.width
                    height: 50
                    Rectangle{
                        id:rec_new_pass
                        width: confirm_pass_text.width+5
                        height: parent.height
                        color: "transparent"
                        Text {
                            id: new_pass_text
                            text: qsTr("New Password")
                            anchors.bottom: parent.bottom
                            color: "white"
                        }

                    }
                    Rectangle{
                        width: parent.width-confirm_pass_text.width
                        height: parent.height
                        color: "transparent"
                        Button{
                        id:see_pass1
                        width: parent.height
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
                            id:neww
                            color: "white"
                            height: 1
                            width: parent.width
                            anchors.bottom: parent.bottom
                        }
                    TextInput{
                        id:newp
                        width: parent.width-see_pass1.width
                        height: 20
                        anchors.bottom: parent.bottom
                        color: "white"
                        clip: true
                        echoMode: TextInput.Password
                        passwordCharacter: "*"
                        EnterKey.type:  Qt.EnterKeyNext
                        onAccepted:  {confirm_pass.focus = true}
                    }
                }
                }

                Row{

                    width: parent.width
                    height: 50
                    Rectangle{
                        id:rec_confirm_pass
                        width: confirm_pass_text.width+5
                        height: parent.height
                        color: "transparent"
                        Text {
                            id: confirm_pass_text
                            text: qsTr("Confirm Password")
                            anchors.bottom: parent.bottom
                            color: "white"
                        }

                    }
                    Rectangle{
                        width: parent.width-confirm_pass_text.width
                        height: parent.height
                        color: "transparent"
                        Button{
                        id:see_pass2
                        width: parent.height
                        height: parent.height
                        background: Rectangle{
                        color: "transparent"
                        }
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        icon.source: "qrc:/glaz1.png"
                        icon.color: "white"

                        onClicked: {
                        confirm_pass.echoMode === TextInput.Password?(confirm_pass.echoMode =TextInput.Normal ) :(confirm_pass.echoMode = TextInput.Password)
                        icon.source == "qrc:/glaz1.png"? icon.source= "qrc:/glaz.png": icon.source= "qrc:/glaz1.png"
                        }
                        }
                        Rectangle {
                            id:conf
                            color: "white"
                            height: 1
                            width: parent.width
                            anchors.bottom: parent.bottom
                        }
                    TextInput{
                        id:confirm_pass
                        width: parent.width-see_pass2.width
                        height: 20
                        anchors.bottom: parent.bottom
                        color: "white"
                        clip: true
                        echoMode: TextInput.Password
                        passwordCharacter: "*"                        
                    }
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
                anchors.top:  column.bottom
                anchors.topMargin: 50
                width: 180
                height: 30
                opacity: enabled ? 1: 0.5
                text: "Save changes"
                enabled: (currentp.text === "" ||newp.text === "" || confirm_pass.text === "" )?false:true
                onClicked: stack00.pop()
            }
        }
    }
}
