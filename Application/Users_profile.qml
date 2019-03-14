import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1
Page{
Rectangle{
    id:back_color
    x: 0
    y: 0
    width: wind.width
    height: wind.height
    clip:true
    gradient: Gradient{
        GradientStop { position: 0.0;color:"dimgrey"}
        GradientStop { position: 0.25;color:"gray"}
        GradientStop { position: 0.5;color:"darkgrey"}
        GradientStop { position: 0.75;color:"silver"}
        GradientStop{ position: 1.0;color:"lightgrey"}
    }
    Rectangle {
        id: rect
        x: 0
        y: 45
        width: wind.width
        height: 1
        color: "#ffffff"
    }
    Rectangle {
        id: rectangle
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin:  toplabel.height + middlelabel.height+ 10//(wind.height)/8
        anchors.bottom: /*tool_bar_form.top*/ parent.bottom
        anchors.bottomMargin: bar.height
        width: wind.width - 60
        height: 350
        color: "transparent"
        TabBar {
            id: bar
            width: parent.width
            TabButton {
                id: tabButton
                text: qsTr("Information")
            }
            TabButton {
                id:tab_stat
                text: qsTr("Statistics")
            }

        }
        StackLayout {
            width: parent.width
            anchors.fill: rectangle
            anchors.topMargin: tabButton.height
            currentIndex: bar.currentIndex
            ListView{
                id:information
                clip: true
                spacing: 3
                model: list_model_info
                delegate:
                    Rectangle{
                    width: rectangle.width
                    height:  50
                    Image {
                        id: stat1
                        source:  "qrc:/taxtak.png"
                        anchors.fill: parent
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            text: name
                            color: "white"
                        }
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.rightMargin: 10
                            anchors.right: parent.right
                            text:number
                            color: "white"
                        }
                    }
                }
                ListModel{
                    id:list_model_info
                    ListElement{
                        name:"Nickname"
                        number:"Valod001"
                    }
                    ListElement{
                        name:"Name"
                        number:"Valod"
                    }
                    ListElement{
                        name:"Surname"
                        number:"Valodyan"
                    }
                    ListElement{
                        name:"Date of birth"
                        number:"22.10.1998"
                    }
                    ListElement{
                        name:"Gender"
                        number:"Male"
                    }
                    ListElement{
                        name:"E-mail"
                        number:"valod001@mail.ru"
                    }
                }
            }
            ListView{
                id:statistic
                spacing: 3
                model: list_model_stat
                clip: true
                delegate:
                    Rectangle{
                    width: rectangle.width
                    height:  50
                    Image {
                        id: stat
                        source:  "qrc:/taxtak.png"
                        anchors.fill: parent
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            text: name
                            color: "white"
                        }
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.rightMargin: 10
                            anchors.right: parent.right
                            text:number
                            color: "white"
                        }
                    }
                }
            }
            ListModel{
                id:list_model_stat
                ListElement{
                    name:"Played games"
                    number:"15"
                }
                ListElement{
                    name:"Red card"
                    number:"5"
                }
                ListElement{
                    name:"Black card"
                    number:"5"
                }
                ListElement{
                    name:"Sheriff"
                    number:"2"
                }
                ListElement{
                    name:"Don"
                    number:"3"
                }
                ListElement{
                    name:"Wins"
                    number:"10"
                }
                ListElement{
                    name:"Fails"
                    number:"5"
                }
                ListElement{
                    name:"Killed"
                    number:"7"
                }
            }

        }
    }
    Label {
        id: toplabel
        x: 0
        y: 0
        width:wind.width
        height: 44
//        Text {
//            id: label_text
//            text: qsTr("MY PROFILE")
//            font.pointSize: 18
//            color: "lightgrey"
//            anchors.centerIn: parent
//        }
        Button {
            id: button
            x: 8
            y: 16
            width: 61
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            Text {
                id: back
                text: qsTr("<")
                anchors.verticalCenterOffset: -3
                anchors.horizontalCenterOffset: 0
                font.pointSize: 30
                color: "white"
                anchors.centerIn: parent
            }
            background: Rectangle{
                color:"transparent"
            }
            onClicked: stackSearch.pop()
        }

        background: Rectangle{
            x:toplabel.x
            y:toplabel.y
            color: "transparent"
        }
    }
    Label {
        id: middlelabel
        x: 0
        y: 45
        width:wind.width
        height: 72
        RoundButton {
            id: roundButton
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 50
            width: 57
            height: 57
            text: "+"
        }
        Button {
            id: name_surname
            anchors.left: parent.left
            anchors.leftMargin: 130
            anchors.top: parent.top
            width: 164
            height: 40
            Text {
                text: qsTr("Hrach Asatryan")
                visible: true
                font.pointSize: 15
                anchors.centerIn: parent
            }
            background: Rectangle{
                color:"transparent"
            }
        }
        ProgressBar {
            id: progressBar
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 147
            anchors.bottomMargin: 20
            width: 93
            height: 6
            value: 0.5
            background: Rectangle{
                radius: 20
            }
        }
        Label {
            id: level
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 248
            anchors.bottomMargin: 15
            text: qsTr("Level 7")
            font.pointSize: 12
        }
    }
    Rectangle{
        id:freespace
        width:Screen.width
        height:(parent.height)/5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: bar.height
        color: "transparent"
    }
}
}
