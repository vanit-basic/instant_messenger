import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.2
import QtQml 2.12
//import QtQml.Models 2.12

Page {
    id:wind

    Rectangle{
        gradient: Gradient{
            GradientStop { position: 0.0;color:"dimgrey"}
            GradientStop { position: 0.25;color:"gray"}
            GradientStop { position: 0.5;color:"darkgrey"}
            GradientStop { position: 0.75;color:"silver"}
            GradientStop{ position: 1.0;color:"lightgrey"}
        }
        anchors.fill: parent
        Rectangle{
            id: rec
            width: (2 * parent.width) / 2.5
            height: (parent.height)/12
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.horizontalCenter:parent.horizontalCenter
            color: "white"
            radius: 30
            Button{
                background:
                    Rectangle{color: "transparent"}
                id: search
                icon.source: "qrc:/search.png"
                icon.color: "teal"
                y: rec.height / 2 - search.height / 2
                width: 55
                height: 55
                anchors.left: parent.left
                anchors.leftMargin: 10
                //                onClicked: {
                //                    if(txt.text != " "){
                //                        console.log("It's alright")
                //                    }
                //                }
            }

            TextField{
                id:txt
                height: rec.height
                color: "black"
                font.pointSize: 15
                clip: true
                anchors.left: parent.left
                anchors.leftMargin: 45
                anchors.right: parent.right
                anchors.rightMargin: 45
                placeholderText: "Search"
                selectByMouse: true
                maximumLength : 100
                enabled: txt.text === " " ? false:true
                background: Rectangle{
                    color: "transparent"
                }
            }

            Button{
                background:
                    Rectangle{color: "transparent"}
                id: cancel
                icon.source: "qrc:/cancel.png"
                icon.color: "teal"
                y: rec.height / 2 - search.height / 2
                width: 54
                height: 54
                anchors.right: parent.right
                anchors.rightMargin: 10
                onClicked: {
                    txt.text = " "
                }
            }
        }

        ToolBar{
            id: toolbar
            anchors.top: rec.bottom
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            background: Rectangle{
                color: "transparent"
            }

            RowLayout{
                ToolButton{
                    icon.source: "avatar.png"
                    text: qsTr("User")
                    icon.color: "teal"
                    onClicked: txt.placeholderText = qsTr("Name, Surname or Nickname")
                    background: Rectangle{
                        color: "transparent"
                    }
                }

                ToolSeparator{}

                ToolButton{
                    icon.source: "users.png"
                    text: qsTr("Group")
                    icon.color: "teal"
                    onClicked: txt.placeholderText = qsTr("Group name")
                    background: Rectangle{
                        color: "transparent"
                    }
                }
                Item { Layout.fillWidth: true }
            }
        }

        Rectangle {
            id:recentsearch
            height: 30
            width: (2 * parent.width) / 2.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: toolbar.bottom
            anchors.topMargin: 20
            color: "transparent"
            Text {
                text: "Recent"
                color: "black"
                anchors.left: parent.left
                anchors.leftMargin: 20
                font.pointSize: 20
            }
        }

        Rectangle {
            id: forlist0
            anchors.top: recentsearch.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            width: (2 * parent.width) / 2.5
            height: 100
            color: "transparent"
            ListModel{
                id: mod0
                ListElement{
                    name: "Sunny"
                }
                ListElement{
                    name: "Jemasita"
                }
                ListElement{
                    name: "Señorita"
                }
            }
            Component {
                id: mod0del
                Text {
                    text: name
                    font.pixelSize: 18
                }
            }
        }


        Rectangle {
            id:recomsearch
            height: 30
            width: (2 * parent.width) / 2.5
            anchors.horizontalCenter: parent.horizontalCenter
            //y: parent.height / 2
            anchors.top: recentsearch.bottom
            anchors.topMargin: 120
            color: "transparent"
            Text {
                text: "Recommended"
                color: "black"
                anchors.left: parent.left
                anchors.leftMargin: 20
                font.pointSize: 20
            }
        }

        Rectangle{
            id: forlist1
            anchors.top: recomsearch.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            width: (2 * parent.width) / 2.5
            height: 100
            color: "transparent"
            ListModel{
                id: mod1
                ListElement{
                    pic: "qrc:/user.png"
                    name: "Hrach"
                }
                ListElement{
                    pic: "qrc:/user.png"
                    name: "Narek"
                }
                ListElement{
                    pic: "qrc:/user.png"
                    name: "Mike"
                }
            }
            Component {
                id: mod1del
                Text {
                    text: name
                    font.pixelSize: 18
                }
            }
        }

        ListView {
            spacing: 7
            anchors.fill: forlist0
            clip: true
            model: mod0
            delegate: mod0del
        }

        ListView {
            spacing: 7
            anchors.fill: forlist1
            clip: true
            model: mod1
            delegate: mod1del
        }
    }
}


