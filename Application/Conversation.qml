import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
Page{
    id: wind1
    Rectangle{
    id:send_show
    visible: false
    width: parent.width-2*user.width
    height: 2*user.height
    x:user.width
    y:user.y-height
    color: "white"
    Button{
    id:send_mess
    width: parent.width
    height: parent.height/2
    anchors.top: parent.top
    anchors.left: parent.left
    text: "Send message"
    background:Rectangle{
    color: "transparent"
    }
    }
    Button{
    id:show_prof
    width: parent.width
    height: parent.height/2
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    text: "Show profile"
    background:Rectangle{
    color: "transparent"
    }
    onClicked: {popup.open();send_show.visible = false}
    }

    }
    Rectangle{
    id:user_page

  anchors.fill:parent
    color: "transparent"
    opacity: 0.5
    Popup{
    id:popup
    width:parent.width-40
    height: parent.height-60
    x:10
    y:40
    background: Rectangle{
    color:"lightgray"
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
            Image{
                anchors.fill:parent
            source: "qrc:/hrach.jpg"
            fillMode: Image.PreserveAspectCrop
            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: mask
            }
            Rectangle{
                id: mask
                width: 50
                height: 50
                radius: 50
                visible: false
            }
            }
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
    Rectangle {
        id: rectangle
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin:  50 + middlelabel.height
        anchors.bottom:  parent.bottom
        anchors.bottomMargin: bar.height
        width: popup.width - 60
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
                        source: "qrc:/taxtak.png"
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
    }
    }
    RoundButton{
        id:user
    height: 50
    width: 50
    Image{
        anchors.fill:parent
    source: "qrc:/hrach.jpg"
    fillMode: Image.PreserveAspectCrop
    layer.enabled: true
    layer.effect: OpacityMask {
        maskSource: mask
    }
    Rectangle{
        id: mask1
        width: 50
        height: 50
        radius: 50
        visible: false
    }
    }
    anchors.verticalCenter: parent.verticalCenter
    onClicked: {
        send_show.visible === true?send_show.visible = false:send_show.visible= true
    }
    }
    header: ToolBar{
        id:top
        Label{
            text: "Miqo"
            anchors.centerIn: parent
        }
        ToolButton{
            text: "<"
            onClicked: {
                stackMess.pop(); swipe.interactive = true ; tab.visible = true
            }
        }
    }
    footer: ToolBar{
        id: root
        width: parent.width
        height: 44
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        Row{
            anchors.fill: parent

            ToolButton{
                background: Rectangle{
                    border.color: "green"
                    radius: 30
                }
                height: 40
                width: height
                id: add
                text: "+"
                font.pixelSize: 25
                //            anchors.left: parent.left
                //            anchors.leftMargin: 5
                anchors.verticalCenter: parent.verticalCenter
            }
            TextField {
                id: textArea
                clip: true
                width: root.width - 95
                wrapMode: "WrapAtWordBoundaryOrAnywhere"
                placeholderText: "Send a message..."



            }


            ToolButton{
                background: Rectangle{
                    border.color: "green"
                    radius: 30
                }
                height: 30
                width: 55
                id: send

                anchors.verticalCenter: parent.verticalCenter
                text: "Send"
            }
        }
    }
}
