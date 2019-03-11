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
                    TextInput{
                        id:currentp
                        width: parent.width-rec_pass.width
                        height: 20
                        anchors.bottom: parent.bottom
                        color: "white"
                        clip: true
                        Rectangle {
                            id:current
                            color: "white"
                            height: 1
                            width: parent.width
                            anchors.bottom: parent.bottom
                        }
                        EnterKey.type:  Qt.EnterKeyNext
                        onEditingFinished:  { newp.focus = true}
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
                    TextInput{
                        id:newp
                        width: parent.width-rec_new_pass.width
                        height: 20
                        anchors.bottom: parent.bottom
                        color: "white"
                        clip: true
                        Rectangle {
                            id:neww
                            color: "white"
                            height: 1
                            width: parent.width
                            anchors.bottom: parent.bottom
                        }
                        EnterKey.type:  Qt.EnterKeyNext
                        onEditingFinished:  {confirm_pass.focus = true}
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
                    TextInput{
                        id:confirm_pass
                        width: parent.width-rec_confirm_pass.width
                        height: 20
                        anchors.bottom: parent.bottom
                        color: "white"
                        clip: true
                        Rectangle {
                            id:conf
                            color: "white"
                            height: 1
                            width: parent.width
                            anchors.bottom: parent.bottom
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
