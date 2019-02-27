import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
//import "qrc:/HomePage.qml" as HomeStack1
Page{
    id:wind
    Drawer {
        id: drawer
        width:  wind.width-rectangle.x-tab_stat.width+50
        height: wind.height//-tool_bar_form.height
        dragMargin: -1

        Rectangle{
        }
        edge: Qt.RightEdge
        background: Rectangle{
            color:"grey"
        }
        Rectangle{
            border.color: "white"
            height:1
            width:parent.width
            anchors.top: parent.top
            anchors.topMargin: 70
        }

        Label{
            id:drawer_lab
            height: 72
            width : drawer.width
            Label{
                id:setlab
                width: drawer.width/15
                anchors.right: drawer_lab.right
                anchors.rightMargin: drawer_lab.width/1.5
                anchors.top: drawer_lab.top
                anchors.topMargin: drawer_lab.height/4
                height:drawer_lab.height/3

                Image {
                    id:settings
                    source: "qrc:/settings.png"
                    width:40
                    height: 40
                }


            }
            Label{
                Text{
                    text: "Settings"
                    font.pointSize: 18
                    color:"lightgrey"
                }
                anchors.top: parent.top
                anchors.topMargin: 22
                anchors.left: parent.left
                anchors.leftMargin: (drawer.width)/2
            }
        }

        Button {
            id: editprofile
            width:(drawer.width)/2
            Text{
                text: " Edit profile"
                color: "white"
                font.pointSize: 15
                anchors.left: parent.left
                anchors.leftMargin: 35
            }

            Button{
                id:editbut
                width: parent.width/12
                height:parent.height*2
                background: Rectangle{
                    color:"transparent"
                }
                Image {
                    id: editphoto
                    source: "qrc:/editprofile.png"
                    height: 30
                    width: 30
                }
            }


            anchors.top: parent.top
            anchors.topMargin: 74
            background:Rectangle{
                color: "transparent"
            }
            onClicked:{
                  drawer.close()
              stack.push(Qt.resolvedUrl("Edit_Profile.qml"))
            }
        }
        Button {
            id: change_pass
            width:(drawer.width)/2
            Text{
                text: " Change Password"
                color: "white"
                font.pointSize: 15
                anchors.left: parent.left
                anchors.leftMargin: 35
            }

            Button{
                id:passbut
                width: parent.width/12
                height:parent.height*2
                background: Rectangle{
                    color:"transparent"
                }
                Image {
                    id: passphoto
                    source: "qrc:/password.png"
                    height: 30
                    width: 30
                }
            }


            anchors.top: parent.top
            anchors.topMargin: 114
            background:Rectangle{
                color: "transparent"
            }
            onClicked: {
                drawer.close()
              // homepage.homeStack.push(Qt.resolvedUrl("Change_Password.qml"))
               stack.push(Qt.resolvedUrl("Change_Password.qml"))
            }
        }


        Button {
            id: change_lang
            width:(drawer.width)/2
            Text{
                text: " Change Language"
                color: "white"
                font.pointSize: 15
                anchors.left: parent.left
                anchors.leftMargin: 35
            }

            Button{
                id:langbut
                width: parent.width/12
                height:parent.height*2
                background: Rectangle{
                    color:"transparent"
                }
                Image {
                    id: langphoto
                    source: "qrc:/language.png"
                    height: 30
                    width: 30
                }
            }


            anchors.top: parent.top
            anchors.topMargin: 154
            background:Rectangle{
                color: "transparent"
            }
        }


        Button {
            id: turn_on
            width:(drawer.width)/2
            Text{
                text: " Turn On/Off Sound"
                color: "white"
                font.pointSize: 15
                anchors.left: parent.left
                anchors.leftMargin: 35
            }

            Button{
                id:turnbut
                width: parent.width/12
                height:parent.height*2
                background: Rectangle{
                    color:"transparent"
                }
                Image {
                    id: turnphoto
                    source: "qrc:/volume.png"
                    height: 30
                    width: 30
                }
            }


            anchors.top: parent.top
            anchors.topMargin: 194
            background:Rectangle{
                color: "transparent"
            }
        }

        Button {
            id: help
            //onClicked: menu.open()
            width:(drawer.width)/2
            Text{
                text: " Help Center"
                color: "white"
                font.pointSize: 15
                anchors.left: parent.left
                anchors.leftMargin: 35
            }

            Button{
                id:helpbut
                width: parent.width/12
                height:parent.height*2
                background: Rectangle{
                    color:"transparent"
                }
                Image {
                    id: helphoto
                    source: "qrc:/support.png"
                    height: 30
                    width: 30
                }
            }


            anchors.top: parent.top
            anchors.topMargin: 234
            background:Rectangle{
                color: "transparent"
            }
        }

        Button {
            id: terms
            width:(drawer.width)/2
            Text{
                text: " Terms and conditions"
                color: "white"
                font.pointSize: 15
                anchors.left: parent.left
                anchors.leftMargin: 35
            }

            Button{
                id:termbut
                width: parent.width/12
                height:parent.height*2
                background: Rectangle{
                    color:"transparent"
                }
                Image {
                    id: termphoto
                    source: "qrc:/terms.png"
                    height: 30
                    width: 30
                }
            }


            anchors.top: parent.top
            anchors.topMargin: 274
            background:Rectangle{
                color: "transparent"
            }
        }

        Button {
            id: sign_out
            width:(drawer.width)/2
            Text{
                text: " Sign Out"
                color: "white"
                font.pointSize: 15
                anchors.left: parent.left
                anchors.leftMargin: 35
            }

            Button{
                id:outbut
                width: parent.width/12
                height:parent.height*2
                background: Rectangle{
                    color:"transparent"
                }
                Image {
                    id: outphoto
                    source: "qrc:/signout.png"
                    height: 30
                    width: 30
                }
            }
            anchors.top: parent.top
            anchors.topMargin: 314
            background:Rectangle{
                color: "transparent"
            }
        }
    }

    Rectangle{
//        ToolBarQml {
//            id:tool_bar_form
//            width: parent.width
//            anchors.bottom: parent.bottom
//        }
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
            width: wind.width - 2*nextbut.width
            height: 350
            color: "transparent"
            TabBar {
                id: bar
                width: parent.width
                TabButton {
                    id:tab_stat
                    text: qsTr("Statistics")
                }
                TabButton {
                    id: tabButton
                    text: qsTr("Information")
                }

            }

            StackLayout {
                width: parent.width
                anchors.fill: rectangle
                anchors.topMargin: tabButton.height
                currentIndex: bar.currentIndex

                //anchors.bottom: wind.bottom
                //anchors.bottomMargin: (Screen.height)/12
                ListView{
                    id:statistic
                    spacing: 3
                    model: list_model_stat
                    clip: true
                    delegate:
                        Rectangle{
                        width: rectangle.width
                        height: /*rectangle.height-tabButton.height*/ 50
                        Image {
                            id: stat
                            source: /*"qrc:/vector-gray-wooden-planks-background.jpg"*/ "qrc:/taxtak.png"
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


                ListView{
                    id:information
                    clip: true
                    spacing: 3
                    model: list_model_info
                    delegate:
                        Rectangle{
                        width: rectangle.width
                        height: /*rectangle.height-tabButton.height*/ 50
                        Image {
                            id: stat1
                            source: /*"qrc:/vector-gray-wooden-planks-background.jpg"*/ "qrc:/taxtak.png"
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
            }
        }

        Label {
            id: toplabel
            x: 0
            y: 0
            width:wind.width
            height: 44
            Text {
                id: label_text
                text: qsTr("MY PROFILE")
                font.pointSize: 18
                color: "lightgrey"
                anchors.centerIn: parent
            }

            Button {
                id: button
                x: 8
                y: 16
                width: 61
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                //           text:qsTr("☰")
                Text {
                    id: back
                    text: qsTr("<")
                    // text: qsTr("☰")
                    anchors.verticalCenterOffset: -3
                    anchors.horizontalCenterOffset: 0
                    font.pointSize: 30
                    color: "white"
                    anchors.centerIn: parent
                }
                background: Rectangle{
                    color:"transparent"
                }
                onClicked: stack.pop()
            }
            Button{
                id:nextbut
                anchors.left: parent.left
                anchors.leftMargin: parent.width-40
                anchors.top: parent.top
                anchors.topMargin: 5
                width: 30
                height: 40
                background: Rectangle{
                    color: "transparent"
                    BorderImage {
                        height: parent.height
                        width:parent.width
                        id: menuph
                        source: "qrc:/menu.png"
                    }
                }
                onClicked: drawer.open()
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
